#include "lumen/app_task.hpp"

#include "lumen/activity/display.hpp"
#include "lumen/activity/snapshot.hpp"
#include "lumen/web/server.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

#include <memory>

namespace lumen {
namespace {

QueueHandle_t message_queue = nullptr;

constexpr auto r1_pin = 32;
constexpr auto g1_pin = 14;
constexpr auto b1_pin = 15;
constexpr auto r2_pin = 27;
constexpr auto g2_pin = 33;
constexpr auto b2_pin = 12;
constexpr auto a_pin = 21;
constexpr auto b_pin = 19;
constexpr auto c_pin = 5;
constexpr auto lat_pin = 7;
constexpr auto oe_pin = 8;
constexpr auto clk_pin = 13;
constexpr auto d_pin = 4;
constexpr auto e_pin = -1;

constexpr auto panel_res_x = 32;
constexpr auto panel_res_y = 16;

constexpr auto num_rows = 3;
constexpr auto num_cols = 3;

} // namespace

void app_task(void* /* parameters */)
{
    message_queue = xQueueCreate(5, sizeof(activity::Message));

    auto message_buffer = activity::Message{};

    HUB75_I2S_CFG::i2s_pins pins = {
        r1_pin,
        g1_pin,
        b1_pin,
        r2_pin,
        g2_pin,
        b2_pin,
        a_pin,
        b_pin,
        c_pin,
        d_pin,
        e_pin,
        lat_pin,
        oe_pin,
        clk_pin
    };

    auto display = std::make_unique<activity::Display>(
        num_rows, num_cols, panel_res_x, panel_res_y, pins
    );

    display->begin();
    display->setBrightness(20);
    display->clearScreen();

    auto web_server = web::Server{};

    auto activity = activity::Snapshot(display.get());

    while (true) {
        xQueueReceive(message_queue, &message_buffer, portMAX_DELAY);

        switch (message_buffer.command) {
        case activity::MessageCommand::increase_score:
            activity.increase_score(message_buffer.team);
            break;
        case activity::MessageCommand::decrease_score:
            activity.decrease_score(message_buffer.team);
            break;
        case activity::MessageCommand::reset:
            activity.reset();
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
