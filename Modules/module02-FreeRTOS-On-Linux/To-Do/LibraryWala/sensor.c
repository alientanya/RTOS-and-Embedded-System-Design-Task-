#include "sensor.h"
#include <stddef.h>

static uint16_t (*hardware_read)(void) = NULL;

void Sensor_Init(uint16_t (*read_func)(void)) {
    hardware_read = read_func;
}

int Sensor_Read(void) {
    if (hardware_read != NULL) {
        return hardware_read();
    }
    return 0; 
}