#include "lumen/button.h"
#include "lumen/display.h"

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#include <iostream>


SemaphoreHandle_t power_button_semaphore = nullptr;
QueueHandle_t power_led_ring_queue = nullptr;


void power_button_init()
{
    gpio_reset_pin(power_red_pin);
    gpio_reset_pin(power_green_pin);
    gpio_reset_pin(power_blue_pin);

    gpio_set_direction(power_normally_open_pin, GPIO_MODE_INPUT);

    // The push button interrupt is triggered on the rising edge
    gpio_set_pull_mode(power_normally_open_pin, GPIO_PULLDOWN_ONLY);

    gpio_set_direction(power_red_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(power_green_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(power_blue_pin, GPIO_MODE_OUTPUT);

    gpio_set_level(power_red_pin, 0);
    gpio_set_level(power_green_pin, 0);
    gpio_set_level(power_blue_pin, 0);
}


void push_button_isr_handler(void* args)
{
    xSemaphoreGiveFromISR(power_button_semaphore, nullptr);
}


void power_button_handler(void* parameters)
{
    TickType_t debounce_period = pdMS_TO_TICKS(300);
    TickType_t end_debounce = 0;
    int count = 0;

    gpio_num_t color_ring[3] = { power_red_pin, power_green_pin, power_blue_pin };
    int color_ring_head = 0;

    power_button_init();

    while (true)
    {
        xSemaphoreTake(power_button_semaphore, portMAX_DELAY);
        end_debounce = xTaskGetTickCount() + debounce_period;

        while (xTaskGetTickCount() < end_debounce) {
            vTaskDelay(200 / portTICK_PERIOD_MS);
            xSemaphoreTake(power_button_semaphore, 0);
            count++;

            if (xTaskGetTickCount() < end_debounce) {
                xSemaphoreTake(power_button_semaphore, end_debounce - xTaskGetTickCount());
            }
        }

        std::cout << "Pressed " << count << " times\n";

        if (count == 1) {
            color_ring_head = (color_ring_head + 1) % 3;
        } else {
            color_ring_head = (color_ring_head + 2) % 3;
        }

        gpio_set_level(color_ring[color_ring_head], 1);
        gpio_set_level(color_ring[(color_ring_head + 1) % 3], 0);
        gpio_set_level(color_ring[(color_ring_head + 2) % 3], 0);

        switch (color_ring_head) {
            case 0:
                change_display_color(150, 0, 0);
                break;
            case 1:
                change_display_color(0, 150, 0);
                break;
            case 2:
                change_display_color(0, 0, 150);
                break;
            default:
                std::cout << "Unknown Input\n";
        }


        count = 0;
    }
}


void power_led_ring_handler(void* parameters)
{
    led_ring_color color;

    while (true) {
        xQueueReceive(power_led_ring_queue, &color, portMAX_DELAY);

        switch (color) {
            case red_ring:
                gpio_set_level(power_red_pin, 1);
                gpio_set_level(power_green_pin, 0);
                gpio_set_level(power_blue_pin, 0);
                break;
            case green_ring:
                gpio_set_level(power_red_pin, 0);
                gpio_set_level(power_green_pin, 1);
                gpio_set_level(power_blue_pin, 0);
                break;
            case blue_ring:
                gpio_set_level(power_red_pin, 0);
                gpio_set_level(power_green_pin, 0);
                gpio_set_level(power_blue_pin, 1);
                break;
            default:
                break;
        }
    }
}
