#include "lumen/app_task.hpp"

#include "lumen/web/server.hpp"

namespace lumen {

void app_task(void* /* parameters */)
{
    auto web_server = web::Server{};

    while (true) {
        vTaskDelay(100);
    }
}

} // namespace lumen
