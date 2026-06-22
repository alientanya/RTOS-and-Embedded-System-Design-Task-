#include <stdio.h>      
#include "sensor.h"     
#include "battery.h"    

int main(void) {
    
    printf("--- Device Booting Up ---\n");

    Sensor_Init();

    while(1){

        int sensor_val = Sensor_Read();
        int battery_val = Battery_ReadVoltage();

        printf("Reading: Sensor Value = %d | Battery = %d \n", sensor_val, battery_val);
    }
    
    return 0;
}