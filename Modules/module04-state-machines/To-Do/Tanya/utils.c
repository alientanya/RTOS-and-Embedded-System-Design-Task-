#include "utils.h"

#include <stdio.h>
#include <unistd.h>
#include "imu.h"

void message(const char *msg){
    printf("%s",msg);
}
void waitms(uint32_t ms){
    usleep(ms*1000);
}
void PrintDeviceData(const imu_data_t *data)
{
    printf("Roll: %.1f  Pitch: %.1f  Yaw: %.1f\n",
           data->roll,
           data->pitch,
           data->yaw);
}