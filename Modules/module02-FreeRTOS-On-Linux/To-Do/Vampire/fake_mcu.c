#include "fake_mcu.h"

#define STATUS_OK            0x00
#define STATUS_LOW_BATTERY   0x01

static uint32_t seed = 12345;
static uint16_t battery_voltage = 4200;

static uint32_t prvPseudoRandom(void)
{
    seed = seed * 1103515245u + 12345u;

    return seed;
}

void MCU_Init(void)
{
    seed = 12345;
    battery_voltage = 4200;
}

uint16_t MCU_ReadADC(void)
{
    return (prvPseudoRandom() % 200u) + 100u;
}

uint16_t MCU_ReadBatteryVoltage(void)
{
    battery_voltage = (prvPseudoRandom() % 1201u) + 3000u;

    return battery_voltage;
}

uint8_t MCU_ReadStatusRegister(void)
{
    if (battery_voltage < 3300u)
    {
        return STATUS_LOW_BATTERY;
    }

    return STATUS_OK;
}