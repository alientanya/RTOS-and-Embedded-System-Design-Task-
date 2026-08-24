#include "imu.h"
#include <stddef.h>

#include <stdbool.h>

/*==========================================================
 * Internal IMU State
 *==========================================================*/

static bool initialized = false;

static float roll = 0.0f;
static float pitch = 0.0f;
static float yaw = 0.0f;


/*==========================================================
 * IMU Initialization
 *==========================================================*/

device_status_t IMU_Init(void)
{
    initialized = true;

    return DEVICE_OK;
}


/*==========================================================
 * IMU Read
 *==========================================================*/

device_status_t IMU_Read(void *data)
{
    imu_data_t *imuData;

    if (!initialized)
        return DEVICE_NOT_INITIALIZED;

    if (data == NULL)
        return DEVICE_ERROR;

    imuData = (imu_data_t *)data;

    roll += 0.5f;
    pitch += 0.2f;
    yaw += 1.0f;

    imuData->roll = roll;
    imuData->pitch = pitch;
    imuData->yaw = yaw;

    return DEVICE_OK;
}


/*==========================================================
 * IMU Reset
 *==========================================================*/

device_status_t IMU_Reset(void)
{
    initialized = false;

    roll = 0.0f;
    pitch = 0.0f;
    yaw = 0.0f;

    return IMU_Init();
}