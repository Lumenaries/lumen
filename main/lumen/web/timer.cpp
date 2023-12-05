#include "lumen/web/timer.h"

#include "esp_log.h"
#include "esp_timer.h"
#include "driver/gptimer.h"

namespace lumen::web {
namespace {

constexpr auto tag = "timer";

float seconds_since_boot() { return esp_timer_get_time() / 1'000'000.0; };

void timer_callback(void* args)
{
    //ESP_LOGI(tag, "Timer callback. Time since boot: %.1f s",
             //seconds_since_boot());
}

} // namespace

void start_timer()
{
    const esp_timer_create_args_t timer_args = {.callback = &timer_callback,
                                                .name = "timer"};

    esp_timer_handle_t timer;
    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &timer));

    ESP_ERROR_CHECK(esp_timer_start_periodic(timer, 100000));
}

Timer::Timer()
{
}



} // namespace lumen::web
