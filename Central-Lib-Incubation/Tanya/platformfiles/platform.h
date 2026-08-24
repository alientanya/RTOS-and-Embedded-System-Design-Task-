#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

/*==========================================================
 * Platform API
 *==========================================================*/

void Platform_Init(void);

void Platform_DelayMs(uint32_t ms);

void Platform_Log(const char *message);

void Platform_LogFloat(
    const char *name,
    float value
);

#endif /* PLATFORM_H */