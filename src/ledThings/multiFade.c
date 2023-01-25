
#include <stdio.h>
#include "freertos\FreeRTOS.h"
#include "freertos\timers.h"
#include "esp_log.h "
#include "esp_err.h"
#include "driver/ledc.h"

#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_HIGH_SPEED_MODE

#define LEDC_OUTPUT_G (19)
#define LEDC_OUTPUT_B (18)
#define LEDC_OUTPUT_R (17)

#define LEDC_CHANNEL_R LEDC_CHANNEL_0
#define LEDC_CHANNEL_G LEDC_CHANNEL_1
#define LEDC_CHANNEL_B LEDC_CHANNEL_2
#define LEDC_CHANNEL_AMOUNT 3

#define LEDC_DUTY_RES LEDC_TIMER_13_BIT
#define LEDC_DUTY (8190)
#define LEDC_FREQUENCY (1000)
#define LEDC_FADE_TIME 1000

#define ESP_INT_FLAG_LEVEL ESP_INTR_FLAG_LEVEL1


static void init_ledc(void)
{
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK
    };

    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    ledc_channel_config_t ledc_channel[3] = {
        {
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL_R,
        .timer_sel = LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LEDC_OUTPUT_R,
        .duty = 0,
        .hpoint = 0
        }, 
        {
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL_G,
        .timer_sel = LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LEDC_OUTPUT_G,
        .duty = 0,
        .hpoint = 0
        },
        {
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL_B,
        .timer_sel = LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LEDC_OUTPUT_B,
        .duty = 0,
        .hpoint = 0
        }
    };

    for (uint8_t i=0; i<LEDC_CHANNEL_AMOUNT; i++)
    {
        ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel[i]));
    } 
}

int app_main(void){
    init_ledc();

    ESP_ERROR_CHECK(ledc_fade_func_install(ESP_INT_FLAG_LEVEL));


    while (1)
    {
        ESP_LOGI("STARTED: ", "RED");
        ESP_ERROR_CHECK(ledc_set_fade_time_and_start(LEDC_MODE,LEDC_CHANNEL_R,
        LEDC_DUTY, LEDC_FADE_TIME, LEDC_FADE_WAIT_DONE));
        ESP_ERROR_CHECK(ledc_set_duty_and_update(LEDC_MODE, LEDC_CHANNEL_R, 0, 0));

        ESP_LOGI("STARTED: ", "GREEN");
        ESP_ERROR_CHECK(ledc_set_fade_time_and_start(LEDC_MODE,LEDC_CHANNEL_G,
        LEDC_DUTY, LEDC_FADE_TIME, LEDC_FADE_WAIT_DONE));
        ESP_ERROR_CHECK(ledc_set_duty_and_update(LEDC_MODE, LEDC_CHANNEL_G, 0, 0));

        ESP_LOGI("STARTED: ", "BLUE");
        ESP_ERROR_CHECK(ledc_set_fade_time_and_start(LEDC_MODE,LEDC_CHANNEL_B,
        LEDC_DUTY, LEDC_FADE_TIME, LEDC_FADE_WAIT_DONE));
        ESP_ERROR_CHECK(ledc_set_duty_and_update(LEDC_MODE, LEDC_CHANNEL_B, 0, 0));

    }

    return 0;
}
