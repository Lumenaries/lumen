#pragma once

#include "esp_http_server.h"

namespace lumen::web::handler {

/** GET handler for the root ("/") endpoint.
 *
 * \param req Pointer to the request being handled.
 */
esp_err_t root(httpd_req_t* req);

} // namespace lumen::web::handler
