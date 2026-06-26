#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

#include "sensor.h"
#include "battery.h"
#include "emergency.h"
#include "system.h"

void SensorTask(void *pvParameters);
void BatteryTask(void *pvParameters);
void EmergencyTask(void *pvParameters);

int main(void)
{
    printf("Starting FreeRTOS Safety Monitoring System...\n");

    system_init();

    xTaskCreate(EmergencyTask, "Emergency", configMINIMAL_STACK_SIZE, NULL, 3, NULL);

    xTaskCreate(SensorTask, "Sensor", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

    xTaskCreate(BatteryTask, "Battery", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    printf("Starting Scheduler...\n");

    vTaskStartScheduler();

    printf("Scheduler failed to start\n");

    return 0;
}

void EmergencyTask(void *pvParameters)
{
    while (1)
    {
        int status = EmergencyStatus();

        printf("[Emergency] Status = %d\n", status);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void SensorTask(void *pvParameters)
{
    while (1)
    {
        int sensor = SensorVal();

        printf("[Sensor] Value = %d\n", sensor);

        vTaskDelay(pdMS_TO_TICKS(800));
    }
}

void BatteryTask(void *pvParameters)
{
    while (1)
    {
        int battery = BatteryVal();

        printf("[Battery] Voltage = %d\n", battery);

        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    printf("Stack Overflow: %s\n", pcTaskName);

    while (1)
    {
    }
}

void vApplicationMallocFailedHook(void)
{
    printf("FATAL ERROR: Memory allocation failed!\n");

    while (1)
    {
        /* Stop here */
    }
}