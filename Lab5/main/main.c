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

void func_CallBack(TimerHandle_t xTimer)
{
   const char *str;
   str = pcTimerGetTimerName(xTimer);

   int Timer_ID = (int) pvTimerGetTimerID(xTimer);

   if (Timer_ID == 0)
   {
      printf("%s _ %d\n",str,++cnt_0);
      if (cnt_0 == 10)
      {
         xTimerStop(xTimer, 0);
         printf("Timer 1 stopped\n");
      }
   }
   else if (Timer_ID == 1)
   {
      printf("==========|| %s _ %d\n",str,++cnt_1);
      if (cnt_1 == 5)
      {
         xTimerStop(xTimer, 0);
         printf("==========|| Timer 2 stopped\n");

      }
   }
}

void app_main()
{
   TaskHandle_t Timer_1 = xTimerCreate("ahihi", pdMS_TO_TICKS(2000),pdTRUE,(void *) 0 , func_CallBack);
   TaskHandle_t Timer_2 = xTimerCreate("ihaha", pdMS_TO_TICKS(3000),pdTRUE,(void *) 1 , func_CallBack);

   xTimerStart(Timer_1, 0);
   xTimerStart(Timer_2, 0);
}
