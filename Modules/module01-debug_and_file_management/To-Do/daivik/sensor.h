#ifndef SENSOR_H
#define SENSOR_H
#include <stdint.h>

void Sensor_Init(uint16_t (*read_func)(void));
int Sensor_Read(void);

#endif