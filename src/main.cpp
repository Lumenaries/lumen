#include "lumen/app_task.hpp"
#include "lumen/net/mdns.hpp"
#include "lumen/net/wifi.hpp"

#include "esp_event.h"
#include "nvs_flash.h"

extern "C" void app_main()
{
    // Create default event loop to handle system-level events
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Initialize NVS needed by Wi-Fi
    ESP_ERROR_CHECK(nvs_flash_init());

    lumen::net::init_wifi_softap();
    lumen::net::init_mdns();

    xTaskCreate(lumen::app_task, "Application Task", 4096, nullptr, 5, nullptr);
}
