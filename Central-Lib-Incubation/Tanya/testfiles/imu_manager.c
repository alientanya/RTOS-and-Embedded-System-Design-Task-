#include "imu_manager.h"
#include <stddef.h>


/*==========================================================
 * IMU Driver Function Table
 *==========================================================*/

static const DeviceDriver imuDriver =
{
    .init = IMU_Init,
    .read = IMU_Read,
    .reset = IMU_Reset
};


/*==========================================================
 * Public API
 *==========================================================*/

void IMUManager_Init(IMUManager *manager)
{
    DeviceManager_Init(
        &manager->device,
        imuDriver,
        &manager->data
    );
}


void IMUManager_Run(IMUManager *manager)
{
    DeviceManager_Run(&manager->device);
}


DeviceState IMUManager_GetState(
    const IMUManager *manager)
{
    return DeviceManager_GetState(
        &manager->device
    );
}


DeviceAction IMUManager_GetLastAction(
    const IMUManager *manager)
{
    return DeviceManager_GetLastAction(
        &manager->device
    );
}


const imu_data_t *IMUManager_GetData(
    const IMUManager *manager)
{
    return &manager->data;
}