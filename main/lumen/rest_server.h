#pragma once

#include "esp_err.h"

namespace lumen {

esp_err_t start_rest_server(const char* base_path);

} // namespace lumen
