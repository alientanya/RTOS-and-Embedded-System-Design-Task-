#include "device_manager.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/*==========================================================
 * Transition Tables
 *==========================================================*/

typedef struct
{
    device_status_t event;
    DeviceAction action;
    DeviceState nextState;

} Transition;

static const Transition t_init[] =
{
    { DEVICE_OK, ACTION_NONE, STATE_RUN },
    { DEVICE_ERROR, ACTION_ERROR, STATE_RESET },
    { DEVICE_DISCONNECTED, ACTION_ERROR, STATE_WAIT }
};

static const Transition t_run[] =
{
    { DEVICE_OK, ACTION_DATA_READY, STATE_RUN },
    { DEVICE_BUSY, ACTION_NONE, STATE_RUN },
    { DEVICE_ERROR, ACTION_ERROR, STATE_RESET },
    { DEVICE_DISCONNECTED, ACTION_ERROR, STATE_WAIT },
    { DEVICE_NOT_INITIALIZED, ACTION_NONE, STATE_INIT }
};

static const Transition t_reset[] =
{
    { DEVICE_OK, ACTION_NONE, STATE_RUN },
    { DEVICE_DISCONNECTED, ACTION_ERROR, STATE_WAIT },
    { DEVICE_ERROR, ACTION_ERROR, STATE_RESET }
};

static const Transition t_wait[] =
{
    { DEVICE_OK, ACTION_NONE, STATE_RUN },
    { DEVICE_DISCONNECTED, ACTION_WAIT, STATE_WAIT },
    { DEVICE_ERROR,  ACTION_ERROR, STATE_RESET }
};


/*==========================================================
 * Process Transition
 *==========================================================*/

static void ProcessTransition(
    DeviceInstance *device,
    device_status_t event,
    const Transition *table,
    int count)
{
    for (int i = 0; i < count; i++)
    {
        if (table[i].event == event)
        {
            device->lastAction = table[i].action;
            device->state = table[i].nextState;

            return;
        }
    }

    device->lastAction = ACTION_NONE;
}


/*==========================================================
 * State Handlers
 *==========================================================*/

static void HandleInit(DeviceInstance *device)
{
    device_status_t status;

    status = device->driver.init();

    ProcessTransition(
        device,
        status,
        t_init,
        ARRAY_SIZE(t_init)
    );
}


static void HandleRun(DeviceInstance *device)
{
    device_status_t status;

    status = device->driver.read(device->data);

    ProcessTransition(
        device,
        status,
        t_run,
        ARRAY_SIZE(t_run)
    );
}


static void HandleReset(DeviceInstance *device)
{
    device_status_t status;

    status = device->driver.reset();

    ProcessTransition(
        device,
        status,
        t_reset,
        ARRAY_SIZE(t_reset)
    );
}


static void HandleWait(DeviceInstance *device)
{
    device_status_t status;

    /*
     * Retry initialization.
     *
     * No delay is performed here.
     * The application/RTOS task controls
     * how frequently DeviceManager_Run()
     * is called.
     */

    status = device->driver.init();

    ProcessTransition(
        device,
        status,
        t_wait,
        ARRAY_SIZE(t_wait)
    );
}


/*==========================================================
 * Public API
 *==========================================================*/

void DeviceManager_Init(
    DeviceInstance *device,
    DeviceDriver driver,
    void *data)
{
    device->driver = driver;
    device->data = data;

    device->state = STATE_INIT;
    device->lastAction = ACTION_NONE;
}


void DeviceManager_Run(DeviceInstance *device)
{
    switch (device->state)
    {
        case STATE_INIT:
            HandleInit(device);
            break;

        case STATE_RUN:
            HandleRun(device);
            break;

        case STATE_RESET:
            HandleReset(device);
            break;

        case STATE_WAIT:
            HandleWait(device);
            break;

        default:
            device->state = STATE_INIT;
            device->lastAction = ACTION_NONE;
            break;
    }
}


DeviceState DeviceManager_GetState(
    const DeviceInstance *device)
{
    return device->state;
}


DeviceAction DeviceManager_GetLastAction(
    const DeviceInstance *device)
{
    return device->lastAction;
}