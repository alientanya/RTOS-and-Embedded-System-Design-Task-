#ifndef IMU_MANAGER_H
#define IMU_MANAGER_H

#include "device_manager.h"
#include "imu.h"


/*==========================================================
 * IMU Manager Instance
 *==========================================================*/

typedef struct
{
    DeviceInstance device;
    imu_data_t data;

} IMUManager;


/*==========================================================
 * Public API
 *==========================================================*/

void IMUManager_Init(IMUManager *manager);

void IMUManager_Run(IMUManager *manager);

DeviceState IMUManager_GetState(
    const IMUManager *manager
);

DeviceAction IMUManager_GetLastAction(
    const IMUManager *manager
);

const imu_data_t *IMUManager_GetData(
    const IMUManager *manager
);

#endif /* IMU_MANAGER_H */