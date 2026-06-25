#include "fake_mcu.h"

static uint32_t seed = 12345;

static uint32_t prvPseudoRandom(void)
{
    seed = seed * 1103515245u + 12345u;

    return seed;
}

void MCU_Init(void)
{
    seed = 12345;
}

uint16_t MCU_ReadADC(void)
{
    return (prvPseudoRandom() % 200u) + 100u;
}

uint16_t MCU_ReadBatteryVoltage(void)
{
    return (prvPseudoRandom() % 1201u) + 3000u;
}

uint8_t MCU_ReadStatusRegister(void)
{
    return (uint8_t)(prvPseudoRandom() & 0xFFu);
}

