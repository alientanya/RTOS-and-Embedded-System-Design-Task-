#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h" 

#include "sensor.h"

QueueHandle_t sensorQueue;

void SensorTask(void *pvParameters);
void DisplayTask(void *pvParameters);

int main(void) {
    printf("--- Booting FreeRTOS Producer-Consumer System ---\n");
    fflush(stdout);

    Sensor_Init();
    sensorQueue = xQueueCreate(10, sizeof(SensorData_t));

    if (sensorQueue != NULL) {

        BaseType_t t1 = xTaskCreate(SensorTask, "Sensor", 256, NULL, 1, NULL);
        BaseType_t t2 = xTaskCreate(DisplayTask, "Display", 256, NULL, 1, NULL);

        if (t1 != pdPASS || t2 != pdPASS) {
            printf("FATAL: Not enough FreeRTOS Heap RAM to create tasks!\n");
            return 1;
        }

        printf("Starting Scheduler...\n");
        fflush(stdout);
        vTaskStartScheduler();
    } else {
        printf("FATAL: Not enough RAM to create the Queue!\n");
    }

    return 0;
}

void SensorTask(void *pvParameters) {
    SensorData_t myData; 

    while(1) {

        myData = Sensor_Read();

        if (xQueueSend(sensorQueue, &myData, pdMS_TO_TICKS(100)) != pdPASS) {
            printf("[WARNING] Queue is full! Dropping Sensor Data.\n");
            fflush(stdout);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void DisplayTask(void *pvParameters) {
    SensorData_t receivedData;

    while(1) {

        if(xQueueReceive(sensorQueue, &receivedData, portMAX_DELAY) == pdPASS) {
 
            // FIXED: Now requesting the actual variables defined in sensor.h
            printf("Received Data - ID: %u, Timestamp: %u\n", receivedData.sensor_id, receivedData.timestamp); 
            
            size_t free_heap = xPortGetFreeHeapSize();

            printf("[DIAGNOSTICS] Free Heap: %zu bytes\n\n", free_heap);
        }
    }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    printf("FATAL ERROR: Stack Overflow in task: %s\n", pcTaskName);
    fflush(stdout);
    while(1); 
}