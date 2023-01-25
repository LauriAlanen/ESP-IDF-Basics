#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h "
#include "driver/gpio.h"

#define BLINK_LED GPIO_NUM_19

int app_main(void){
    char *ourTask = pcTaskGetName(NULL); // NULL Will make a query for it's own name 
    ESP_LOGI(ourTask, "Hello Starting up!\n"); // Basically the same as Serial.print


    gpio_reset_pin(BLINK_LED); 
    gpio_set_direction(BLINK_LED, GPIO_MODE_DEF_OUTPUT); // Set the BLINK_LED pin as an output.

    while (1)
    {
        gpio_set_level(BLINK_LED, 1); // Set the BLINK_LED pin HIGH.
        vTaskDelay(1000/portTICK_PERIOD_MS); // Calculate the delay time using the tick rate
        gpio_set_level(BLINK_LED, 0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    
}
