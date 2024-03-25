idf_component_register(SRCS
                           "lumen/activity/display.cpp"
                           "lumen/activity/snapshot.cpp"
                           "lumen/app_task.cpp"
                           "lumen/net/mdns.cpp"
                           "lumen/net/wifi.cpp"
                           "lumen/web/server.cpp"
                           "main.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES
                            ESP32-HUB75-MatrixPanel-DMA
                            esp_event
                            esp_http_server
                            esp_hw_support  # esp_mac
                            esp_netif
                            esp_wifi
                            log             # esp_log
                            lwip
                            mdns
                            nvs_flash
                        )
