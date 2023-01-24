#include <stdio.h>
#include "freertos\FreeRTOS.h"
#include "freertos\timers.h"
#include "esp_log.h "
#include "esp_err.h"
#include "driver/ledc.h"

#define LEDC_TIMER LEDC_TIMER_0 // Select timer 0
#define LEDC_MODE LEDC_LOW_SPEED_MODE // Set the speed mode to LOW
#define LEDC_OUTPUT_IO (19) //GPIO 19   
#define LEDC_CHANNEL LEDC_CHANNEL_0 // Set the channel to 0
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT // Use 13 Bit timer
#define LEDC_DUTY (8190) // Because we use 13-bit timer 8190 corresponds 100% duty cycle.
#define LEDC_FREQUENCY (1000) // Well here you can set the frequency

#define FADE_DELAY 7 // The time between every duty cycle change in the for loops.

static void init_ledc(void) 
{
    ledc_timer_config_t ledc_timer = { // This struct contains all the configurations of timer.
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK
    };

    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer)); // Pass the timer config struct here


    ledc_channel_config_t ledc_channel = { // This struct contains all the configurations of channel.
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LEDC_OUTPUT_IO,
        .duty = 0,
        .hpoint = 0
    };

    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel)); // Pass the channel config struct here
}



int app_main(void){ 
    init_ledc(); // Call the init_ledc function which has all the configs
    while (1)
    {
        for (int i=0; i<LEDC_DUTY; i++) // Change the duty cycle one step at a time until it hits 8190
        {
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, i)); // Set the duty cycle here
            ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL)); // Apply the update
            vTaskDelay(FADE_DELAY/portTICK_PERIOD_MS); // Wait for FADE_DELAY amount of ms.
        }
        for (int i=LEDC_DUTY; i>0; i--)   // Change the duty cycle one step at a time until it hits 0
        {
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, i));
            ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
            vTaskDelay(FADE_DELAY/portTICK_PERIOD_MS);
        }

    }
    return 0;
}
