#include "lumen/dns_server.h"
#include "lumen/filesystem.h"
#include "lumen/rest_server.h"
#include "lumen/wifi.h"

#include "esp_event.h" // esp_event_loop_create_default()
#include "esp_netif.h" // esp_netif_init()
#include "nvs_flash.h" // nvs_flash_init()
#include "esp_wifi.h"  // sp_netif_create_default_wifi_ap()

extern "C" void app_main()
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Initialize Wi-Fi including netif with default config
    esp_netif_create_default_wifi_ap();

    lumen::initialize_mdns();
    lumen::wifi_init_softap();
    lumen::start_dns_server();

    ESP_ERROR_CHECK(lumen::init_fs());
    ESP_ERROR_CHECK(lumen::start_rest_server(CONFIG_EXAMPLE_WEB_MOUNT_POINT));
}
