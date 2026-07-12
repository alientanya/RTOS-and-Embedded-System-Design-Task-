#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "sensor.h"

QueueHandle_t sensorQueue;

void SensorTask(void *pvParameters);
void DisplayTask(void *pvParameters);

int main(void)
{
    printf("=== Queue Demo ===\n");

    Sensor_Init();

    sensorQueue = xQueueCreate(10, sizeof(SensorData_t));

    if (sensorQueue == NULL)
    {
        printf("Failed to create queue!\n");
        while (1);
    }

    if (xTaskCreate(SensorTask,
                    "SensorTask",
                    configMINIMAL_STACK_SIZE,
                    NULL,
                    2,
                    NULL) != pdPASS)
    {
        printf("Failed to create SensorTask!\n");
        while (1);
    }

    if (xTaskCreate(DisplayTask,
                    "DisplayTask",
                    configMINIMAL_STACK_SIZE,
                    NULL,
                    1,
                    NULL) != pdPASS)
    {
        printf("Failed to create DisplayTask!\n");
        while (1);
    }

    printf("Starting Scheduler...\n");
    vTaskStartScheduler();
    printf("Scheduler failed!\n");

    while(1);

    return 0;
}

void SensorTask(void *pvParameters)
{
    SensorData_t data;

    while(1)
    {
        data = Sensor_Read();

        xQueueSend(sensorQueue, &data, portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void DisplayTask(void *pvParameters)
{
    SensorData_t receivedData;

    while(1)
    {
        if(xQueueReceive(sensorQueue, &receivedData, portMAX_DELAY) == pdPASS)
        {
            printf("\n");
            printf("Sensor ID   : %u\n", receivedData.sensor_id);
            printf("Timestamp   : %u\n", receivedData.timestamp);
            printf("----------------------------\n");
        }
    }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    printf("Stack overflow in %s\n", pcTaskName);
    while(1);
}

void vApplicationMallocFailedHook(void)
{
    printf("Malloc Failed!\n");
    while(1);
}