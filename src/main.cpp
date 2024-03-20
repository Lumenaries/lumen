#include "lumen/net/wifi.hpp"
#include "lumen/web/server.hpp"

#include "esp_event.h"
#include "nvs_flash.h"

extern "C" void app_main()
{
    // Create default event loop to handle system-level events
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Initialize NVS needed by Wi-Fi
    ESP_ERROR_CHECK(nvs_flash_init());

    lumen::net::init_wifi_softap();

    // TODO: Start an "Application" task that creates the web server and passes
    // it to the functions/tasks that need it.
    auto web_server = lumen::web::Server{};

    while (true) {
        vTaskDelay(1);
    }
}
