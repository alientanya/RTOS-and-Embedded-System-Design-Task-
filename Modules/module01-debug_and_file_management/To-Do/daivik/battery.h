#ifndef BATTERY_H
#define BATTERY_H
#include <stdint.h>

void Battery_Init(uint16_t (*read_func)(void));
int Battery_ReadVoltage(void);

#endif