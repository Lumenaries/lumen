#include "lumen/button.h"
#include "lumen/display.h"

#include "driver/gpio.h"
#include "esp_intr_alloc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#include <iostream>


extern "C" void app_main()
{
    power_button_init();
    display_init();

    power_button_semaphore = xSemaphoreCreateBinary();
    power_led_ring_queue = xQueueCreate(1, sizeof(led_ring_color));

    ESP_ERROR_CHECK(gpio_set_intr_type(power_normally_open_pin, GPIO_INTR_POSEDGE));
    ESP_ERROR_CHECK(gpio_install_isr_service(0));
    ESP_ERROR_CHECK(gpio_isr_handler_add(power_normally_open_pin, push_button_isr_handler, nullptr));

    xTaskCreate(power_button_handler, "Power Button Handler", 4096, nullptr, 5, nullptr);
    xTaskCreate(power_led_ring_handler, "Button Ring Handler", 4096, nullptr, 5, nullptr);
}
