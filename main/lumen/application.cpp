#include "lumen/application.h"

#include "lumen/net/dns_server.h"
#include "lumen/net/wifi.h"
#include "lumen/sys/button.h"
#include "lumen/sys/display.h"
#include "lumen/sys/filesystem.h"
#include "lumen/web/rest_server.h"

#include "driver/gpio.h"
#include "esp_event.h" // esp_event_loop_create_default()
#include "esp_intr_alloc.h"
#include "esp_netif.h" // esp_netif_init()
#include "esp_wifi.h"  // sp_netif_create_default_wifi_ap()
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
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

    power_button_init();
    display_init();

    power_button_semaphore = xSemaphoreCreateBinary();
    power_led_ring_queue = xQueueCreate(1, sizeof(led_ring_color));

    ESP_ERROR_CHECK(
        gpio_set_intr_type(power_normally_open_pin, GPIO_INTR_POSEDGE));
    ESP_ERROR_CHECK(gpio_install_isr_service(0));
    ESP_ERROR_CHECK(gpio_isr_handler_add(power_normally_open_pin,
                                         push_button_isr_handler, nullptr));

    xTaskCreate(power_button_handler, "Power Button Handler", 4096, nullptr, 5,
                nullptr);
    xTaskCreate(power_led_ring_handler, "Button Ring Handler", 4096, nullptr, 5,
                nullptr);
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
