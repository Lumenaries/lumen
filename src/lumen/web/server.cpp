#include "lumen/web/server.hpp"

#include "esp_http_server.h"
#include "esp_log.h"

namespace lumen::web {
namespace {

constexpr auto tag = "server";

esp_err_t root_handler(httpd_req_t* req);

} // namespace

/**
 */
void init_http_server()
{
    httpd_handle_t server = nullptr;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.uri_match_fn = httpd_uri_match_wildcard;

    ESP_LOGI(tag, "Starting web server");
    if (httpd_start(&server, &config) != ESP_OK) {
        ESP_LOGE(tag, "Failed to start the web server");
        return;
    }

    httpd_uri_t root_uri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = root_handler,
    };
    httpd_register_uri_handler(server, &root_uri);
}

namespace {

esp_err_t root_handler(httpd_req_t* req)
{
    httpd_resp_send(req, "<h1>Hello World!</h1>", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

} // namespace

} // namespace lumen::web
