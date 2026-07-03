#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>

typedef struct
{
    uint32_t sensor_id;
    uint32_t timestamp;
    char description[512];
} SensorData_t;

void Sensor_Init(void);

SensorData_t Sensor_Read(void);

#endif