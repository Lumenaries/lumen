#include "lumen/app_task.hpp"

#include "lumen/web/server.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace lumen {
namespace {

constexpr auto tag = "app_task";

} // namespace

// What should this task do?
// - Start the web server
// - Start the Display
// - Switch between different activities
void app_task(void* /*parameters*/)
{
    auto web_server = lumen::web::Server{};

    while (true) {
        vTaskDelay(100);
    }
}

} // namespace lumen
