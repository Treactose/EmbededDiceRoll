#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"

#define light1 19
#define light2 18
#define light3 21
#define light4 17
#define light5 16
#define light6 4
#define rollBtn 5

static void roll(int r) {
    switch(r) {
        case 1:
            gpio_set_level(light1, 1);
            gpio_set_level(light2, 0);
            gpio_set_level(light3, 0);
            gpio_set_level(light4, 0);
            gpio_set_level(light5, 0);
            gpio_set_level(light6, 0);
            break;
        case 2:
            gpio_set_level(light1, 1);
            gpio_set_level(light2, 1);
            gpio_set_level(light3, 0);
            gpio_set_level(light4, 0);
            gpio_set_level(light5, 0);
            gpio_set_level(light6, 0);
            break;
        case 3:
            gpio_set_level(light1, 1);
            gpio_set_level(light2, 1);
            gpio_set_level(light3, 1);
            gpio_set_level(light4, 0);
            gpio_set_level(light5, 0);
            gpio_set_level(light6, 0);
            break;
        case 4:
            gpio_set_level(light1, 1);
            gpio_set_level(light2, 1);
            gpio_set_level(light3, 1);
            gpio_set_level(light4, 1);
            gpio_set_level(light5, 0);
            gpio_set_level(light6, 0);
            break;
        case 5:
            gpio_set_level(light1, 1);
            gpio_set_level(light2, 1);
            gpio_set_level(light3, 1);
            gpio_set_level(light4, 1);
            gpio_set_level(light5, 1);
            gpio_set_level(light6, 0);
            break;
        case 6:
            gpio_set_level(light1, 1);
            gpio_set_level(light2, 1);
            gpio_set_level(light3, 1);
            gpio_set_level(light4, 1);
            gpio_set_level(light5, 1);
            gpio_set_level(light6, 1);
            break;
    }
}

void app_main(void) {
    gpio_set_direction(light1, GPIO_MODE_OUTPUT);
    gpio_set_direction(light2, GPIO_MODE_OUTPUT);
    gpio_set_direction(light3, GPIO_MODE_OUTPUT);
    gpio_set_direction(light4, GPIO_MODE_OUTPUT);
    gpio_set_direction(light5, GPIO_MODE_OUTPUT);
    gpio_set_direction(light6, GPIO_MODE_OUTPUT);
    gpio_set_direction(rollBtn, GPIO_MODE_INPUT);
    gpio_set_pull_mode(rollBtn, GPIO_PULLUP_ONLY);
    srand(time(NULL));

    while(1) {
        int button = gpio_get_level(rollBtn);
        ESP_LOGI("Input","%d",button);
        if(button == 0) {
            vTaskDelay(pdMS_TO_TICKS(50));
            if(gpio_get_level(rollBtn) == 0) {
                int r = (random() % 6) + 1;
                ESP_LOGI("Dice", "Rolled: %d", r);
                roll(r);
                vTaskDelay(pdMS_TO_TICKS(500));
            }
        }else{
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
}
