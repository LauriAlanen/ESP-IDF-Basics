#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h "
#include "driver/gpio.h"

#define BLINK_LED GPIO_NUM_19

int app_main(void){
    char *ourTask = pcTaskGetName(NULL);
    ESP_LOGI(ourTask, "Hello Starting up!\n");


    gpio_reset_pin(BLINK_LED);
    gpio_set_direction(BLINK_LED, GPIO_MODE_DEF_OUTPUT);

    while (1)
    {
        gpio_set_level(BLINK_LED, 1);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        gpio_set_level(BLINK_LED, 0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    
}