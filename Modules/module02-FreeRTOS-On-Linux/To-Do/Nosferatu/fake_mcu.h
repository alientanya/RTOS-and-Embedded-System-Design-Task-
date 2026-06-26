#ifndef FAKE_MCU_H
#define FAKE_MCU_H

#include <stdint.h>

/* Initialize fake hardware. */
void MCU_Init(void);

/* Simulated ADC read. */
uint16_t MCU_ReadADC(void);

/* Simulated battery voltage read. */
uint16_t MCU_ReadBatteryVoltage(void);

/* Simulated device status register. */
uint8_t MCU_ReadStatusRegister(void);

#endif
