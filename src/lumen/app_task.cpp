#include "lumen/app_task.hpp"

#include "lumen/activity/display.hpp"
#include "lumen/activity/snapshot.hpp"
#include "lumen/web/server.hpp"

#include <memory>

namespace lumen {
namespace {

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

constexpr auto num_rows = 1;
constexpr auto num_cols = 1;

} // namespace

void app_task(void* /* parameters */)
{
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
    display->setBrightness(50);
    display->clearScreen();

    auto web_server = web::Server{};

    auto activity = activity::Snapshot(display.get());

    while (true) {
        vTaskDelay(100);
    }
}

} // namespace lumen
