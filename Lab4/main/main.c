#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

xQueueHandle school;

typedef struct {
   char name[3];
   int age;
   int error;
} student;



void reception(void* pvParameter)
{
   student data_holder;
   srand(time(0));
   char *i = 'A';
   while (1)
   {
      data_holder.age = (rand() % (40 - 1 + 1)) + 1;
      strcpy(data_holder.name,&i);
      i++;
      xQueueSend(school,&data_holder,portMAX_DELAY);
      printf("\n\n Add name: %s , age: %d into queue !!! \n\n",data_holder.name,data_holder.age);
      vTaskDelay(pdMS_TO_TICKS(500));
   }
}

void func_1_Primary(void* pvParameter)
{
   if (school == NULL)
   {
      printf("School is empty !!! \n");
      return;
   }
   else
   {
      TaskHandle_t tsk;
      tsk = xTaskGetCurrentTaskHandle();
      student data_receiver;
      while (1)
      {
         if(xQueueReceive(school,&data_receiver,pdMS_TO_TICKS(1000)) == pdPASS)
         {
            printf("\n\n func_1 name: %s , age: %d !!! \n\n",data_receiver.name,data_receiver.age);
            if (data_receiver.age >= 6 && data_receiver.age <= 10)
            {
               printf("%s is %d and studies in %s \n",data_receiver.name,data_receiver.age,pcTaskGetTaskName(tsk));
            }
            else 
            {
               data_receiver.error++;
               xQueueSend(school,&data_receiver,portMAX_DELAY);
               printf("error func_1 !!! \n");
            }
         }
         vTaskDelay(pdMS_TO_TICKS(1000));
      }
   }
}

void func_2_Junior(void* pvParameter)
{
   if (school == NULL)
   {
      printf("School is empty !!!");
      return;
   }
   else
   {
      TaskHandle_t tsk;
      tsk = xTaskGetCurrentTaskHandle();
      student data_receiver;
      while (1)
      {
         if(xQueueReceive(school,&data_receiver,pdMS_TO_TICKS(1000)) == pdPASS)
         {
            printf("\n\n func_2 name: %s , age: %d !!! \n\n",data_receiver.name,data_receiver.age);
            if (data_receiver.age >= 11 && data_receiver.age <= 15)
            {
               printf("%s is %d and studies in %s \n",data_receiver.name,data_receiver.age,pcTaskGetTaskName(tsk));
            }
            else 
            {
               data_receiver.error++;
               xQueueSend(school,&data_receiver,portMAX_DELAY);
               printf("error func_2 !!! \n");
            }
         }
         vTaskDelay(pdMS_TO_TICKS(1000));
      }
   }
}

void func_3_High(void* pvParameter)
{
   if (school == NULL)
   {
      printf("School is empty !!! \n");
      return;
   }
   else
   {
      TaskHandle_t tsk;
      tsk = xTaskGetCurrentTaskHandle();
      student data_receiver;
      while (1)
      {
         if(xQueueReceive(school,&data_receiver,pdMS_TO_TICKS(1000)) == pdPASS)
         {
            printf("\n\n func_3 name: %s , age: %d !!! \n\n",data_receiver.name,data_receiver.age);
            if (data_receiver.age >= 16 && data_receiver.age <= 18)
            {
               printf("%s is %d and studies in %s \n",data_receiver.name,data_receiver.age,pcTaskGetTaskName(tsk));
            }
            else 
            {
               data_receiver.error++;
               xQueueSend(school,&data_receiver,portMAX_DELAY);
               printf("error func_3 !!! \n");
            }  
         }
         vTaskDelay(pdMS_TO_TICKS(1000));
      }
   }
}

void func_4_Uni(void* pvParameter)
{
   if (school == NULL)
   {
      printf("School is empty !!! \n");
      return;
   }
   else
   {
      TaskHandle_t tsk;
      tsk = xTaskGetCurrentTaskHandle();
      student data_receiver;
      while (1)
      {
         if(xQueueReceive(school,&data_receiver,pdMS_TO_TICKS(100)) == pdPASS)
         {
            printf("\n\n func_4 name: %s , age: %d !!! \n\n",data_receiver.name,data_receiver.age);
            if (data_receiver.age >= 19 && data_receiver.age <= 23)
            {
               printf("%s is %d and studies in %s \n",data_receiver.name,data_receiver.age,pcTaskGetTaskName(tsk));
            }
            else 
            {
               data_receiver.error++;
               xQueueSend(school,&data_receiver,portMAX_DELAY);
               printf("error func_4 !!! \n");
            }
         }
         vTaskDelay(pdMS_TO_TICKS(1000));
      }
   }
}

void func_5_Ignore(void* pvParameter)
{
   if (school == NULL)
   {
      printf("func_5 is null\n");
      return;
   }
   else
   {
      student data_receiver;
      while (1)
      {
         if(xQueueReceive(school,&data_receiver,pdMS_TO_TICKS(100)) == pdPASS)
         {
            printf("\n\n func_5 name: %s , age: %d !!! \n\n",data_receiver.name,data_receiver.age);
            if ((data_receiver.age <= 5 || data_receiver.age >= 24) || data_receiver.error == 4)
            {
               printf("Ignore name: %s , age: %d !!! \n",data_receiver.name,data_receiver.age);
            }
            else 
            {
               data_receiver.error++;
               xQueueSend(school,&data_receiver,portMAX_DELAY);
               printf("error func_5 !!! \n");
            }
         }
         vTaskDelay(pdMS_TO_TICKS(600));
      }
   }
}

void app_main()
{
   school = xQueueCreate(2,sizeof(student));
   xTaskCreate(&reception, "reception", 2048, NULL, 1, NULL);
   xTaskCreate(&func_1_Primary, "Primary School", 2048, NULL, 1, NULL);
   xTaskCreate(&func_2_Junior, "Junior high school", 2048, NULL, 1, NULL);
   xTaskCreate(&func_3_High, "High school", 2048, NULL, 1, NULL);
   xTaskCreate(&func_4_Uni, "University", 2048, NULL, 1, NULL);
   xTaskCreate(&func_5_Ignore, "Ignore", 2048, NULL, 2, NULL);
}
