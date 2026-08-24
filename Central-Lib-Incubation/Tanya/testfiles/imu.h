#ifndef IMU_H
#define IMU_H

#include "device_types.h"

/*==========================================================
 * IMU Data
 *==========================================================*/

typedef struct
{
    float roll;
    float pitch;
    float yaw;

} imu_data_t;


/*==========================================================
 * IMU Driver API
 *==========================================================*/

device_status_t IMU_Init(void);

device_status_t IMU_Read(void *data);

device_status_t IMU_Reset(void);

#endif /* IMU_H */