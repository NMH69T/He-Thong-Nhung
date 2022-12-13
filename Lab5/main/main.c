#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

int cnt_0 = 0;
int cnt_1 = 0;

TimerHandle_t Timer_1;
TimerHandle_t Timer_2;

void func_CallBack(TimerHandle_t xTimer)
{
    TickType_t time = xTaskGetTickCount() / 1000;

    if (xTimer == Timer_1)
    {
        cnt_0++;
        printf("At %ds: ahihi call %d times", time, cnt_0);
        if (cnt_0 >= 10)
        {
            xTimerStop(xTimer, 0);
            printf(" ===> ahihi stops");
        }
    }
    if (xTimer == Timer_2)
    {
        cnt_1++;
        printf("At %ds: ihaha call %d times", time, cnt_1);
        if (cnt_1 >= 5)
        {
            xTimerStop(xTimer, 0);
            printf(" ===> ihaha stops");
        }
    }
    printf("\n");
}

void app_main()
{
    Timer_1 = xTimerCreate("AHIHI", pdMS_TO_TICKS(2000), pdTRUE, 0, func_CallBack);
    Timer_2 = xTimerCreate("IHAHA", pdMS_TO_TICKS(3000), pdTRUE, 1, func_CallBack);

    xTimerStart(Timer_1, 0);
    xTimerStart(Timer_2, 0);
}
