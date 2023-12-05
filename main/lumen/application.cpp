#include "lumen/application.h"

#include "lumen/net/dns_server.h"
#include "lumen/net/wifi.h"
#include "lumen/sys/filesystem.h"
#include "lumen/web/rest_server.h"
#include "lumen/web/timer.h"

#include "esp_event.h" // esp_event_loop_create_default()
#include "esp_netif.h" // esp_netif_init()
#include "esp_wifi.h"  // sp_netif_create_default_wifi_ap()
#include "nvs_flash.h" // nvs_flash_init()

namespace lumen {

void start()
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Initialize Wi-Fi including netif with default config
    esp_netif_create_default_wifi_ap();

    net::initialize_mdns();
    net::wifi_init_softap();
    net::start_dns_server();

    ESP_ERROR_CHECK(sys::init_fs());
    ESP_ERROR_CHECK(web::start_rest_server(CONFIG_EXAMPLE_WEB_MOUNT_POINT));

    web::start_timer();
}

/*
Application::Application()
{
    web_server_t server{config...};

    server.register_uri_handler(&led_uri);
    server.register_uri_handler(&common_get_uri);
}

class web_server_t {
public:
    web_server_t(config...) {
        httpd_start(&server, &config);
    }

    register_uri_handler(const httpd_uri_t uri);

private:
    std::unique_ptr<rest_context_> context_;
    httpd_handle_t server = nullptr;
};
*/

} // namespace lumen
