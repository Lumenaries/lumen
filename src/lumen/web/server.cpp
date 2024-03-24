#include "lumen/web/server.hpp"

#include "lumen/web/handler/root.hpp"
#include "lumen/web/handler/start_timer.hpp"

#include "esp_http_server.h"
#include "esp_log.h"

namespace lumen::web {
namespace {

constexpr auto tag = "web/server";

/** Register all of the endpoints.
 *
 * \param server A reference to a valid http server handle.
 */
void register_endpoints(httpd_handle_t& server);

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

void register_endpoints(httpd_handle_t& server)
{
    httpd_uri_t root_uri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = handler::root,
        .user_ctx = nullptr
    };
    httpd_register_uri_handler(server, &root_uri);

    httpd_uri_t start_timer_uri = {
        .uri = "/start_timer",
        .method = HTTP_GET,
        .handler = handler::start_timer,
        .user_ctx = nullptr
    };

    httpd_register_uri_handler(server, &start_timer_uri);
}

} // namespace

} // namespace lumen::web
