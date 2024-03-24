idf_component_register(SRCS
                           "lumen/activity/message.cpp"
                           "lumen/app_task.cpp"
                           "lumen/net/wifi.cpp"
                           "lumen/web/handler/root.cpp"
                           "lumen/web/handler/start_timer.cpp"
                           "lumen/web/server.cpp"
                           "main.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES
                            driver
                            esp_event
                            esp_http_server
                            esp_hw_support  # esp_mac
                            esp_netif
                            esp_wifi
                            log             # esp_log
                            lwip
                            nvs_flash
                        )
