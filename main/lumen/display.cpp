#include "lumen/display.h"

#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"


const int panel_res_x = 32;
const int panel_res_y = 16;

const int num_rows = 1;
const int num_cols = 1;

const int r1_pin    = 5;
const int g1_pin    = 42;
const int b1_pin    = 6;
const int r2_pin    = 7;
const int g2_pin    = 41;
const int b2_pin    = 15;
const int a_pin     = 16;
const int b_pin     = 40;
const int c_pin     = 17;
const int d_pin     = 38;
const int e_pin     = -1;
const int lat_pin   = 39;
const int oe_pin    = 8;
const int clk_pin   = 18;

MatrixPanel_I2S_DMA* display = nullptr;
HUB75_I2S_CFG::i2s_pins pins = {r1_pin, g1_pin, b1_pin,
                                r2_pin, g2_pin, b2_pin,
                                a_pin, b_pin, c_pin, d_pin,
                                e_pin, lat_pin, oe_pin, clk_pin};


void display_init()
{
    HUB75_I2S_CFG mxconfig(panel_res_x, panel_res_y, 1, pins);

    display = new MatrixPanel_I2S_DMA(mxconfig);
    display->begin();
    display->setBrightness8(5);
    display->clearScreen();
}


void change_display_color(int8_t red, int8_t green, int8_t blue)
{
    display->fillScreenRGB888(red, green, blue);
}
