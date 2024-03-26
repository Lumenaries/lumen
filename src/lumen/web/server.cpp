#include "lumen/web/server.hpp"

#include "lumen/app_task.hpp"

#include "esp_http_server.h"
#include "esp_log.h"
#include "esp_vfs.h"

#include <fcntl.h>
#include <string>

namespace lumen::web {
namespace {

constexpr auto tag = "web/server";

/** Register all of the endpoints.
 *
 * \param server A reference to a valid http server handle.
 */
void register_endpoints(httpd_handle_t& server);

/**
 *
 */
bool check_file_extension(char const* filepath, char const* ext);

/**
 */
esp_err_t set_content_type_from_file(httpd_req_t* req, char const* filepath);

} // namespace

Server::Server()
{
    ESP_LOGI(tag, "Starting web server");

    config.uri_match_fn = httpd_uri_match_wildcard;

    httpd_start(&server, &config);
    register_endpoints(server);
}

Server::~Server()
{
    ESP_LOGI(tag, "Stopping web server");
    httpd_stop(server);
}

namespace {

/** GET handler for the root ("/") endpoint.
 *
 * \param req Pointer to the request being handled.
 */
esp_err_t root_handler(httpd_req_t* req)
{
    constexpr auto html =
        "<h1>Hello World!</h1>"
        "<div>"
        "<a style='margin-right: 5px;' href='/increase_one'>increase_one</a>"
        "<a href='/decrease_one'>decrease_one</a>"
        "</div>"
        "<div>"
        "<a href='/increase_two'>increase_two </a>"
        "<a style='margin-right: 15px;' href='/decrease_two'>decrease_two</a>"
        "</div>";
    httpd_resp_send(req, html, HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}

esp_err_t increase_one_handler(httpd_req_t* req)
{
    send_message_to_app(
        {activity::MessageCommand::increase_score, activity::Team::home}
    );

    return root_handler(req);
}

esp_err_t decrease_one_handler(httpd_req_t* req)
{
    send_message_to_app(
        {activity::MessageCommand::decrease_score, activity::Team::home}
    );

    return root_handler(req);
}

esp_err_t increase_two_handler(httpd_req_t* req)
{
    send_message_to_app(
        {activity::MessageCommand::increase_score, activity::Team::away}
    );

    return root_handler(req);
}

esp_err_t decrease_two_handler(httpd_req_t* req)
{
    send_message_to_app(
        {activity::MessageCommand::decrease_score, activity::Team::away}
    );

    return root_handler(req);
}

esp_err_t common_get_handler(httpd_req_t* req)
{
    uint32_t filepath_max = ESP_VFS_PATH_MAX + 128;
    char filepath[filepath_max] = "/www";

    if (req->uri[strlen(req->uri) - 1] == '/') {
        strlcat(filepath, "/index.html", sizeof(filepath));
    } else {
        strlcat(filepath, req->uri, sizeof(filepath));
    }

    int fd = open(filepath, O_RDONLY, 0);
    if (fd == -1) {
        ESP_LOGE(tag, "Failed to open file : %s", filepath);

        // Respond with 500 Internal Server Error
        httpd_resp_send_err(
            req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to read existing file"
        );
        return ESP_FAIL;
    }

    set_content_type_from_file(req, filepath);

    uint32_t scratch_buffer_size = 10240;
    char chunk[scratch_buffer_size];
    ssize_t read_bytes;

    do {
        // Read the file in the scratch buffer in chunks
        read_bytes = read(fd, chunk, scratch_buffer_size);

        if (read_bytes == -1) {
            ESP_LOGE(tag, "Failed to read file : %s", filepath);
        } else if (read_bytes > 0) {
            // Send the buffer contents as HTTP response chunk
            if (httpd_resp_send_chunk(req, chunk, read_bytes) != ESP_OK) {
                close(fd);
                ESP_LOGE(tag, "File sending failed!");

                // Abort sending file
                httpd_resp_sendstr_chunk(req, nullptr);

                // Respond with 500 Internal Server Error
                httpd_resp_send_err(
                    req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to send file"
                );

                return ESP_FAIL;
            }
        }
    } while (read_bytes > 0);

    // Close file after sending complete
    close(fd);
    ESP_LOGI(tag, "File sending complete");

    // Respond with an empty chunk to signal HTTP response completion
    httpd_resp_send_chunk(req, nullptr, 0);

    return ESP_OK;
}

void register_endpoints(httpd_handle_t& server)
{
    httpd_uri_t root_uri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = root_handler,
        .user_ctx = nullptr
    };
    httpd_register_uri_handler(server, &root_uri);

    httpd_uri_t increase_one_uri = {
        .uri = "/increase_one",
        .method = HTTP_GET,
        .handler = increase_one_handler,
        .user_ctx = nullptr
    };
    httpd_register_uri_handler(server, &increase_one_uri);

    httpd_uri_t decrease_one_uri = {
        .uri = "/decrease_one",
        .method = HTTP_GET,
        .handler = decrease_one_handler,
        .user_ctx = nullptr
    };
    httpd_register_uri_handler(server, &decrease_one_uri);

    httpd_uri_t increase_two_uri = {
        .uri = "/increase_two",
        .method = HTTP_GET,
        .handler = increase_two_handler,
        .user_ctx = nullptr
    };
    httpd_register_uri_handler(server, &increase_two_uri);

    httpd_uri_t decrease_two_uri = {
        .uri = "/decrease_two",
        .method = HTTP_GET,
        .handler = decrease_two_handler,
        .user_ctx = nullptr
    };
    httpd_register_uri_handler(server, &decrease_two_uri);

    httpd_uri_t common_get_uri = {
        .uri = "/*",
        .method = HTTP_GET,
        .handler = common_get_handler,
        .user_ctx = nullptr
    };
    httpd_register_uri_handler(server, &common_get_uri);
}

bool check_file_extension(char const* filepath, char const* ext)
{
    return strcasecmp(&filepath[strlen(filepath) - strlen(ext)], ext) == 0;
}

esp_err_t set_content_type_from_file(httpd_req_t* req, char const* filepath)
{
    const char* type = "text/plain";

    if (check_file_extension(filepath, ".html")) {
        type = "text/html";
    } else if (check_file_extension(filepath, ".js")) {
        type = "application/javascript";
    } else if (check_file_extension(filepath, ".css")) {
        type = "text/css";
    } else if (check_file_extension(filepath, ".png")) {
        type = "image/png";
    } else if (check_file_extension(filepath, ".ico")) {
        type = "image/x-icon";
    } else if (check_file_extension(filepath, ".svg")) {
        type = "image/svg+xml";
    }

    return httpd_resp_set_type(req, type);
}

} // namespace

} // namespace lumen::web
