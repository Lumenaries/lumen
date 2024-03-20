#include "lumen/web/server.hpp"

#include "esp_http_server.h"
#include "esp_log.h"

namespace lumen::web {
namespace {

constexpr auto tag = "web/server";

void register_endpoints(httpd_handle_t& server);
esp_err_t root_handler(httpd_req_t* req);

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

/** \brief Register all of the endpoints.
 *
 * \param server A reference to a valid http server handle.
 */
void register_endpoints(httpd_handle_t& server)
{
    httpd_uri_t root_uri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = root_handler,
        .user_ctx = nullptr
    };
    httpd_register_uri_handler(server, &root_uri);
}

/// GET handler for the root ("/") endpoint.
esp_err_t root_handler(httpd_req_t* req)
{
    httpd_resp_send(req, "<h1>Hello World!</h1>", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

} // namespace

} // namespace lumen::web
