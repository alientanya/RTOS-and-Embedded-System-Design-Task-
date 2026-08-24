#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "device_types.h"

/*==========================================================
 * Device State
 *==========================================================*/

typedef enum
{
    STATE_INIT,
    STATE_RUN,
    STATE_RESET,
    STATE_WAIT
} DeviceState;


/*==========================================================
 * Device Actions
 *==========================================================*/

typedef enum
{
    ACTION_NONE,
    ACTION_DATA_READY,
    ACTION_ERROR,
    ACTION_WAIT
} DeviceAction;


/*==========================================================
 * Driver Function Pointers
 *==========================================================*/

typedef device_status_t (*DeviceInitFunc)(void);

typedef device_status_t (*DeviceReadFunc)(void *data);

typedef device_status_t (*DeviceResetFunc)(void);


/*==========================================================
 * Device Driver Interface
 *==========================================================*/

typedef struct
{
    DeviceInitFunc init;
    DeviceReadFunc read;
    DeviceResetFunc reset;

} DeviceDriver;


/*==========================================================
 * Device Instance
 *==========================================================*/

typedef struct
{
    DeviceDriver driver;

    void *data;

    DeviceState state;

    DeviceAction lastAction;

} DeviceInstance;


/*==========================================================
 * Public API
 *==========================================================*/

void DeviceManager_Init(
    DeviceInstance *device,
    DeviceDriver driver,
    void *data
);

void DeviceManager_Run(
    DeviceInstance *device
);

DeviceState DeviceManager_GetState(
    const DeviceInstance *device
);

DeviceAction DeviceManager_GetLastAction(
    const DeviceInstance *device
);

#endif /* DEVICE_MANAGER_H */