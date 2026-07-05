#include "imu_manager.h"
#include "utils.h"

#include <unistd.h>

int main(void)
{
    IMUManager_Init();

    while (1)
    {
        IMUManager_Run();
        waitms(100);
    }

    return 0;
}