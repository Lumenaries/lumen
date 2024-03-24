#pragma once

#include "esp_http_server.h"

namespace lumen::web::handler {

esp_err_t start_timer(httpd_req_t* req);

} // namespace lumen::web::handler
