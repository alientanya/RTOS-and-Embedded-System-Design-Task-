#include "battery.h"
#include <stddef.h>

static uint16_t (*hardware_read)(void) = NULL;

void Battery_Init(uint16_t (*read_func)(void)) {
    hardware_read = read_func;
}

int Battery_ReadVoltage(void) {
    if (hardware_read != NULL) {
        return hardware_read();
    }
    return 0;
}
