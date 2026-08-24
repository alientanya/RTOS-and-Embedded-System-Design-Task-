#include "platform_linux.h"

#include <stdio.h>
#include <unistd.h>


void Platform_Init(void)
{
    /* Linux platform initialization */
}


void Platform_DelayMs(uint32_t ms)
{
    usleep(ms * 1000);
}


void Platform_Log(const char *message)
{
    printf("%s", message);
}


void Platform_LogFloat(
    const char *name,
    float value)
{
    printf("%s: %.2f\n", name, value);
}