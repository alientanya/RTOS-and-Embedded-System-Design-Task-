#include "sensor.h"

#include <string.h>

static uint32_t timestamp_counter = 0;

void Sensor_Init(void)
{
    timestamp_counter = 0;
}

SensorData_t Sensor_Read(void)
{
    SensorData_t data;

    data.sensor_id = 1;
    data.timestamp = timestamp_counter++;

    memset(
        data.description,
        'A',
        sizeof(data.description) - 1);

    data.description[
        sizeof(data.description) - 1] = '\0';

    return data;
}