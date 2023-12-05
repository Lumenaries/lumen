#include "server.h"

#include <filesystem>

Server::Server(const std::string& base_path) {}

esp_err_t Server::set_content_type_from_file(
    httpd_req_t* req, const std::filesystem::path& filepath) {

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

esp_err_t Server::rest_common_get_handler(httpd_req_t* req) {}
