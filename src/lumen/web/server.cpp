#include "lumen/web/server.hpp"

#include "lumen/app_task.hpp"

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

/** GET handler for the root ("/") endpoint.
 *
 * \param req Pointer to the request being handled.
 */
esp_err_t root_handler(httpd_req_t* req)
{
    constexpr auto html = "<h1>Hello World!</h1>"
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
}

} // namespace

} // namespace lumen::web
