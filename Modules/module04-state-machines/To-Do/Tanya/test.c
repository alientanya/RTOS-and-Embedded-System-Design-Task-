#include "imu_manager.h"
#include "imu.h"
#include "utils.h"

#include <stdio.h>

int main(void)
{
    IMUManager_Init();
    message("Device Test\n");

    while (1)
    {
        IMUManager_Run();

        switch (IMUManager_GetState())
        {
            case STATE_INIT:
                message("State: INIT\n");
                break;

            case STATE_READ:
                message("State: READ\n");
                break;

            case STATE_RESET:
                message("State: RESET\n");
                break;

            case STATE_WAIT_RECONNECT:
                message("State: WAIT_RECONNECT\n");
                break;

            default:
                message("State: UNKNOWN\n");
                break;
        }

        switch (IMUManager_GetLastAction())
        {
            case ACTION_PRINT_DATA:
            {
                const imu_data_t *data = IMUManager_GetData();

                printf("Roll: %.1f  Pitch: %.1f  Yaw: %.1f\n",
                       data->roll,
                       data->pitch,
                       data->yaw);
                break;
            }

            case ACTION_PRINT_ERR:
                message("IMU operation failed\n");
                break;

            case ACTION_WAIT:
                waitms(100);
                break;

            case ACTION_NONE:
            default:
                break;
        }

        waitms(100);
    }

    return 0;
}