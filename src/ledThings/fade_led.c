#include <stdio.h>
#include "freertos\FreeRTOS.h"
#include "freertos\timers.h"
#include "esp_log.h "
#include "esp_err.h"
#include "driver/ledc.h"

#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_HIGH_SPEED_MODE
#define LEDC_OUTPUT_IO (19)
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT
#define LEDC_DUTY (8190)
#define LEDC_FREQUENCY (1000)
#define ESP_INT_FLAG_LEVEL ESP_INTR_FLAG_LEVEL1

#define LEDC_FADE_TIME 400

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


    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LEDC_OUTPUT_IO,
        .duty = 0,
        .hpoint = 0
    };

    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}



int app_main(void){
    init_ledc();

    ESP_ERROR_CHECK(ledc_fade_func_install(ESP_INT_FLAG_LEVEL));

    while (1)
    {
        ESP_ERROR_CHECK(ledc_set_fade_time_and_start(
        LEDC_MODE,
        LEDC_CHANNEL,
        LEDC_DUTY,
        LEDC_FADE_TIME,
        LEDC_FADE_NO_WAIT
    ));
        ESP_ERROR_CHECK(ledc_set_fade_time_and_start(
        LEDC_MODE,
        LEDC_CHANNEL,
        0,
        LEDC_FADE_TIME,
        LEDC_FADE_NO_WAIT
    ));
    }
    
    return 0;
}
