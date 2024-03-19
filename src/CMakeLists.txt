idf_component_register(SRCS
                           "main.cpp"
                           "lumen/net/wifi.cpp"
                           "lumen/web/server.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES
                            esp_event
                            esp_http_server
                            esp_hw_support  # esp_mac
                            esp_netif
                            esp_wifi
                            log             # esp_log
                            lwip
                            nvs_flash
                        )
