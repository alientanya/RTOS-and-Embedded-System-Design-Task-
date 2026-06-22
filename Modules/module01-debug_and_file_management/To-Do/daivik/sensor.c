#include "sensor.h"  
#include "fake_mcu.h" 

void Sensor_Init(void) {
    MCU_Init(); 
}
int Sensor_Read(void) {
    int raw_value = MCU_ReadADC();
    
     return raw_value;
}