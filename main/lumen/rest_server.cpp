#include "lumen/rest_server.h"

#include "cJSON.h"
#include "driver/gpio.h"
#include "esp_chip_info.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "esp_random.h"
#include "esp_vfs.h"

#include <fcntl.h>
#include <string.h>

namespace {

constexpr auto tag = "rest_server";

} // namespace

namespace lumen {

const gpio_num_t led_pin = GPIO_NUM_13;

#define FILE_PATH_MAX (ESP_VFS_PATH_MAX + 128)
#define SCRATCH_BUFSIZE (10240)

typedef struct rest_server_context {
    char base_path[ESP_VFS_PATH_MAX + 1];
    char scratch[SCRATCH_BUFSIZE];
} rest_server_context_t;

#define CHECK_FILE_EXTENSION(filename, ext)                                    \
    (strcasecmp(&filename[strlen(filename) - strlen(ext)], ext) == 0)

/* Set HTTP response content type according to file extension */
static esp_err_t set_content_type_from_file(httpd_req_t* req,
                                            const char* filepath)
{
    const char* type = "text/plain";

    if (CHECK_FILE_EXTENSION(filepath, ".html")) {
        type = "text/html";
    } else if (CHECK_FILE_EXTENSION(filepath, ".js")) {
        type = "application/javascript";
    } else if (CHECK_FILE_EXTENSION(filepath, ".css")) {
        type = "text/css";
    } else if (CHECK_FILE_EXTENSION(filepath, ".png")) {
        type = "image/png";
    } else if (CHECK_FILE_EXTENSION(filepath, ".ico")) {
        type = "image/x-icon";
    } else if (CHECK_FILE_EXTENSION(filepath, ".svg")) {
        type = "image/svg+xml";
    }
    return httpd_resp_set_type(req, type);
}

/* Send HTTP response with the contents of the requested file */
static esp_err_t rest_common_get_handler(httpd_req_t* req)
{
    char filepath[FILE_PATH_MAX];

    rest_server_context_t* rest_context = (rest_server_context_t*)req->user_ctx;
    strlcpy(filepath, rest_context->base_path, sizeof(filepath));
    if (req->uri[strlen(req->uri) - 1] == '/') {
        strlcat(filepath, "/index.html", sizeof(filepath));
    } else {
        strlcat(filepath, req->uri, sizeof(filepath));
    }
    int fd = open(filepath, O_RDONLY, 0);
    if (fd == -1) {
        ESP_LOGE(tag, "Failed to open file : %s", filepath);
        /* Respond with 500 Internal Server Error */
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR,
                            "Failed to read existing file");
        return ESP_FAIL;
    }

    set_content_type_from_file(req, filepath);

    char* chunk = rest_context->scratch;
    ssize_t read_bytes;
    do {
        /* Read file in chunks into the scratch buffer */
        read_bytes = read(fd, chunk, SCRATCH_BUFSIZE);
        if (read_bytes == -1) {
            ESP_LOGE(tag, "Failed to read file : %s", filepath);
        } else if (read_bytes > 0) {
            /* Send the buffer contents as HTTP response chunk */
            if (httpd_resp_send_chunk(req, chunk, read_bytes) != ESP_OK) {
                close(fd);
                ESP_LOGE(tag, "File sending failed!");
                /* Abort sending file */
                httpd_resp_sendstr_chunk(req, NULL);
                /* Respond with 500 Internal Server Error */
                httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR,
                                    "Failed to send file");
                return ESP_FAIL;
            }
        }
    } while (read_bytes > 0);
    /* Close file after sending complete */
    close(fd);
    ESP_LOGI(tag, "File sending complete");
    /* Respond with an empty chunk to signal HTTP response completion */
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

esp_err_t led_handler(httpd_req_t* req)
{
    int total_len = req->content_len;
    int cur_len = 0;
    char* buf = ((rest_server_context_t*)(req->user_ctx))->scratch;
    int received = 0;
    if (total_len >= SCRATCH_BUFSIZE) {
        /* Respond with 500 Internal Server Error */
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR,
                            "content too long");
        return ESP_FAIL;
    }
    while (cur_len < total_len) {
        received = httpd_req_recv(req, buf + cur_len, total_len);
        if (received <= 0) {
            /* Respond with 500 Internal Server Error */
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR,
                                "Failed to post control value");
            return ESP_FAIL;
        }
        cur_len += received;
    }
    buf[total_len] = '\0';

    cJSON* root = cJSON_Parse(buf);

    bool led_on;
    if (cJSON_GetObjectItem(root, "led on")->type == cJSON_True) {
        led_on = true;
    } else {
        led_on = false;
    }
    ESP_LOGI(tag, "LED: %d", led_on);

    gpio_set_level(led_pin, led_on);

    cJSON* response = cJSON_CreateObject();
    cJSON_AddBoolToObject(response, "led on", led_on);
    const char* button_status = cJSON_Print(response);

    httpd_resp_sendstr(req, button_status);

    free((void*)button_status);
    cJSON_Delete(response);

    cJSON_Delete(root);
    return ESP_OK;
}

esp_err_t start_rest_server(const char* base_path)
{
    if (base_path == nullptr) {
        ESP_LOGE(tag, "Empty base path");
        return ESP_FAIL;
    }

    rest_server_context_t* rest_context =
        (rest_server_context*)calloc(1, sizeof(rest_server_context_t));

    if (rest_context == nullptr) {
        ESP_LOGE(tag, "No memory for rest context");
        return ESP_FAIL;
    }

    strlcpy(rest_context->base_path, base_path,
            sizeof(rest_context->base_path));

    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.uri_match_fn = httpd_uri_match_wildcard;

    ESP_LOGI(tag, "Starting HTTP Server");
    if (httpd_start(&server, &config) != ESP_OK) {
        ESP_LOGE(tag, "Start server failed");
        free(rest_context);
    }

    ESP_LOGI(tag, "Initializing led_pin");
    gpio_reset_pin(led_pin);
    gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);

    httpd_uri_t led_uri = {.uri = "/api/v1/led",
                           .method = HTTP_POST,
                           .handler = led_handler,
                           .user_ctx = rest_context};
    httpd_register_uri_handler(server, &led_uri);

    /* URI handler for getting web server files */
    httpd_uri_t common_get_uri = {.uri = "/*",
                                  .method = HTTP_GET,
                                  .handler = rest_common_get_handler,
                                  .user_ctx = rest_context};
    httpd_register_uri_handler(server, &common_get_uri);

    return ESP_OK;
}

} // namespace lumen
