#include "cJSON.h"
#include "esp_chip_info.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "esp_random.h"
#include "esp_vfs.h"

#include <fcntl.h>

#include <filesystem>
#include <memory>
#include <string>

namespace {

struct rest_server_context_t {
    std::filesystem::path base_path;
    std::string scratch;
};

esp_err_t set_content_type_from_file(httpd_req_t* req,
                                     const std::filesystem::path& filepath)
{
    auto* mime_type = [&filepath] {
        if (filepath.extension() == ".html") {
            return "text/html";
        } else if (filepath.extension() == ".js") {
            return "application/javascript";
        } else if (filepath.extension() == ".css") {
            return "text/css";
        } else if (filepath.extension() == ".png") {
            return "image/png";
        } else if (filepath.extension() == ".ico") {
            return "image/x-icon";
        } else if (filepath.extension() == ".svg") {
            return "image/svg+xml";
        } else {
            return "text/plain";
        }
    }();

    return httpd_resp_set_type(req, mime_type);
}

esp_err_t rest_common_get_handler(httpd_req_t* req)
{
    rest_server_context_t* rest_context =
        static_cast<rest_server_context_t*>(req->user_ctx);

    std::filesystem::path filepath{rest_context->base_path};
}

esp_err_t start_rest_server(const std::filesystem::path& base_path)
{
    auto rest_context =
        std::make_unique<rest_server_context_t>(std::move(base_path));

    httpd_handle_t server = nullptr;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.uri_match_fn = httpd_uri_match_wildcard;

    httpd_start(&server, &config);

    httpd_uri_t common_get_uri = {.uri = "/*",
                                  .method = HTTP_GET,
                                  .handler = rest_common_get_handler,
                                  .user_ctx = rest_context};
    httpd_register_uri_handler(server, &common_get_uri);
    return ESP_OK;
}

} // namespace
