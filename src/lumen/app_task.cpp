#include "lumen/app_task.hpp"

#include "lumen/web/server.hpp"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace lumen {
namespace {

constexpr auto tag = "app_task";

QueueHandle_t message_queue = nullptr;

} // namespace

// What should this task do?
// - Start the web server
// - Start the Display
// - Switch between different activities
void app_task(void* /*parameters*/)
{
    message_queue = xQueueCreate(5, sizeof(activity::Message));

    // Can message_queue fail to be allocated?
    if (message_queue == nullptr) {
        ESP_LOGE(tag, "Failed to create message_queue");
        vTaskDelete(nullptr);
    }

    auto message_buffer = activity::Message{};
    auto web_server = web::Server{};

    while (true) {
        xQueueReceive(message_queue, &message_buffer, portMAX_DELAY);

        switch (message_buffer.command) {
        case activity::MessageCommand::start_timer:
            ESP_LOGI(tag, "Start timer");
            break;
        case activity::MessageCommand::stop_timer:
            ESP_LOGI(tag, "Stop timer");
            break;
        case activity::MessageCommand::activate_buzzer:
            ESP_LOGI(tag, "Activate buzzer");
            break;
        case activity::MessageCommand::change_team_name:
            ESP_LOGI(tag, "Change team name");
            break;
        case activity::MessageCommand::increase_score:
            ESP_LOGI(tag, "Increase score");
            break;
        case activity::MessageCommand::decrease_score:
            ESP_LOGI(tag, "Decrease score");
            break;
        default:
            ESP_LOGI(tag, "Received nothing");
            break;
        }
    }
}

void send_message_to_app(activity::Message const& message)
{
    // We don't want to lose messages, so wait for as long as necessary
    xQueueSendToBack(message_queue, &message, portMAX_DELAY);
}

} // namespace lumen
