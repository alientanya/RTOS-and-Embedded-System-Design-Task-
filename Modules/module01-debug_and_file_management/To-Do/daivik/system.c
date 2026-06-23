#include "system.h"
#include "../fake_mcu.h"
#include "sensor.h"
#include "battery.h"

void System_Init(void) {

    MCU_Init();

    Sensor_Init(MCU_ReadADC);
    Battery_Init(MCU_ReadBatteryVoltage);
}