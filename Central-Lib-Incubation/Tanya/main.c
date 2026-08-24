#include <stdio.h>

#include "imu_manager.h"


/*==========================================================
 * Helper Functions
 *==========================================================*/

static const char *StateToString(DeviceState state)
{
    switch (state)
    {
        case STATE_INIT:
            return "INIT";

        case STATE_RUN:
            return "RUN";

        case STATE_RESET:
            return "RESET";

        case STATE_WAIT:
            return "WAIT";

        default:
            return "UNKNOWN";
    }
}


static const char *ActionToString(DeviceAction action)
{
    switch (action)
    {
        case ACTION_NONE:
            return "NONE";

        case ACTION_DATA_READY:
            return "DATA_READY";

        case ACTION_ERROR:
            return "ERROR";

        case ACTION_WAIT:
            return "WAIT";

        default:
            return "UNKNOWN";
    }
}


/*==========================================================
 * Main
 *==========================================================*/

int main(void)
{
    IMUManager imu1;
    IMUManager imu2;

    /* Initialize two IMU manager instances */
    IMUManager_Init(&imu1);
    IMUManager_Init(&imu2);

    printf("========================================\n");
    printf("     Device Manager / IMU Demo\n");
    printf("========================================\n\n");

    for (int i = 0; i < 20; i++)
    {
        /* Run both IMU state machines */
        IMUManager_Run(&imu1);
        IMUManager_Run(&imu2);

        /* Get current state and action */
        DeviceState state1 = IMUManager_GetState(&imu1);
        DeviceAction action1 = IMUManager_GetLastAction(&imu1);

        DeviceState state2 = IMUManager_GetState(&imu2);
        DeviceAction action2 = IMUManager_GetLastAction(&imu2);

        printf("IMU 1: State = %-6s | Action = %-11s\n",
               StateToString(state1),
               ActionToString(action1));

        if (action1 == ACTION_DATA_READY)
        {
            const imu_data_t *data = IMUManager_GetData(&imu1);

            printf("       Roll = %.2f | Pitch = %.2f | Yaw = %.2f\n",
                   data->roll,
                   data->pitch,
                   data->yaw);
        }

        printf("IMU 2: State = %-6s | Action = %-11s\n",
               StateToString(state2),
               ActionToString(action2));

        if (action2 == ACTION_DATA_READY)
        {
            const imu_data_t *data = IMUManager_GetData(&imu2);

            printf("       Roll = %.2f | Pitch = %.2f | Yaw = %.2f\n",
                   data->roll,
                   data->pitch,
                   data->yaw);
        }

        printf("----------------------------------------\n");
    }

    return 0;
}