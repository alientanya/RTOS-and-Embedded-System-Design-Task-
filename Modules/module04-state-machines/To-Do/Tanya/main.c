#include "imu_manager.h"

#include <unistd.h>

int main(void)
{
    IMUManager_Init();

    while (1)
    {
        IMUManager_Run();
        usleep(100000);
    }

    return 0;
}