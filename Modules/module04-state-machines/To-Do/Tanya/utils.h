#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include "imu.h"

void message(const char *message);
void waitms(uint32_t ms);
void PrintDeviceData(const imu_data_t *data);
#endif