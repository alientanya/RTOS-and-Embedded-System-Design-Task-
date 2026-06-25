#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "sensor.h"
#include "battery.h"
#include "emergency.h"
#include "system.h"

void EmergencyTask(void *pvParameters);
void SensorTask(void *pvParameters);
void BatteryTask(void *pvParameters);

int main(void) {
    printf("--- Booting FreeRTOS Safety System ---\n");

    System_Init();
    Battery_Init();
    xTaskCreate(EmergencyTask, "Emergency", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    xTaskCreate(SensorTask, "Sensor", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(BatteryTask, "Battery", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    printf("Starting Scheduler...\n");
    vTaskStartScheduler();
    printf("ERROR: Scheduler Failed to Start!\n");
    return 0;
}

void EmergencyTask(void *pvParameters) {
    while(1) {
        uint8_t status = EmergencyStatus();
        printf("[EMERGENCY TASK] Safety Status Code: %d\n", status);

        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void SensorTask(void *pvParameters) {
    while(1) {
        int sensor_val = Sensor_Read();
        printf("[SENSOR TASK] Sensor Reading: %d\n", sensor_val);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void BatteryTask(void *pvParameters) {
    while(1) {
        int battery_val = Battery_ReadVoltage(); 
        printf("[BATTERY TASK] Battery Voltage: %d\n", battery_val);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    printf("FATAL ERROR: Stack Overflow in task: %s\n", pcTaskName);
    while(1); /* Freeze the system */
}