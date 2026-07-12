#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

void Platform_Write(const char *data);

uint32_t Platform_DelayMs(void);

#endif

