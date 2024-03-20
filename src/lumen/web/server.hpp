#pragma once

#include "esp_http_server.h"

namespace lumen::web {

/** \brief Handles the creation and destruction of HTTP web servers.
 */
struct Server {
    httpd_handle_t server = nullptr;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    Server();
    ~Server();
};

} // namespace lumen::web
