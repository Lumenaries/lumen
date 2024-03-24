#include "lumen/web/handler/root.hpp"

namespace lumen::web::handler {

esp_err_t root(httpd_req_t* req)
{
    char const* html = "<h1>Hello World!</h1>"
                       "<a href='/start_timer'>Start Timer</a>";
    httpd_resp_send(req, html, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

} // namespace lumen::web::handler
