#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BTN_NUM 14
#define STUDENT_ID 1913439

int btn_cnt = 0;

void btn_check(void *pvParameter)
{
    gpio_pad_select_gpio(BTN_NUM);
    gpio_set_direction(BTN_NUM,GPIO_MODE_INPUT);
    gpio_set_pull_mode(BTN_NUM,GPIO_PULLUP_ONLY);
    while (1) // 
    {
        if (gpio_get_level(BTN_NUM) == 0)    btn_cnt++;
        else btn_cnt = 0;

        if (btn_cnt >= 2)    printf("ESP32\n");
         vTaskDelay (100 / portTICK_PERIOD_MS ) ;
    }
    vTaskDelete(NULL);
}

// void print_id(void *pvParameter)
// {
//     while (1)
//     {
//         printf("%d\n",STUDENT_ID);
//          vTaskDelay (1000 / portTICK_PERIOD_MS ) ;
//     }
//     vTaskDelete(NULL);
// }

void app_main()
{
    xTaskCreate(&btn_check,"buttons",8000,NULL,1,NULL);
   // xTaskCreate(&print_id,"student id",8000,NULL,0,NULL);
    while (1)
    {
        printf("%d\n",STUDENT_ID);
        vTaskDelay (1000 / portTICK_PERIOD_MS ) ;
    }
    
}

