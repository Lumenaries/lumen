#pragma once

#include "esp_wifi.h"

#include <cstdint>

namespace lumen::net {

void initialize_mdns();

void wifi_event_handler(void* arg, esp_event_base_t event_base,
                        int32_t event_id, void* event_data);

void wifi_init_softap();

} // namespace lumen::net
