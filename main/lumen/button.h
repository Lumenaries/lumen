#pragma once


#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"


const gpio_num_t power_normally_open_pin    = GPIO_NUM_14;
const gpio_num_t power_red_pin              = GPIO_NUM_11;
const gpio_num_t power_green_pin            = GPIO_NUM_12;
const gpio_num_t power_blue_pin             = GPIO_NUM_13;

extern SemaphoreHandle_t power_button_semaphore;
extern QueueHandle_t power_led_ring_queue;

enum led_ring_color {
    red_ring,
    green_ring,
    blue_ring
};


void power_button_init();
void push_button_isr_handler(void* parameters);
void power_button_handler(void* parameters);
void power_led_ring_handler(void* parameters);
