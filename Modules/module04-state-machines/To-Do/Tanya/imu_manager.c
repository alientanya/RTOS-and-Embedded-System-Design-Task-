#include "imu_manager.h"
#include "imu.h"
#include "utils.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef enum
{
    STATE_INIT,
    STATE_READ,
    STATE_RESET,
    STATE_WAIT_RECONNECT
} AppState;

typedef enum
{
    ACTION_NONE,
    ACTION_PRINT_DATA,
    ACTION_PRINT_ERR,
    ACTION_WAIT
} Action;

typedef struct
{
    imu_status_t event;
    Action action;
    AppState nextState;
} Transition;

static AppState state;
static imu_data_t data;

static const Transition t_init[] = {
    { IMU_OK,           ACTION_NONE,      STATE_READ },
    { IMU_ERROR,        ACTION_PRINT_ERR, STATE_RESET },
    { IMU_DISCONNECTED, ACTION_PRINT_ERR, STATE_WAIT_RECONNECT }
};

static const Transition t_read[] = {
    { IMU_OK,              ACTION_PRINT_DATA, STATE_READ },
    { IMU_NO_NEW_DATA,     ACTION_WAIT,       STATE_READ },
    { IMU_ERROR,           ACTION_PRINT_ERR,  STATE_RESET },
    { IMU_DISCONNECTED,    ACTION_PRINT_ERR,  STATE_WAIT_RECONNECT },
    { IMU_NOT_INITIALIZED, ACTION_NONE,       STATE_INIT }
};

static const Transition t_reset[] = {
    { IMU_OK,           ACTION_NONE,      STATE_READ },
    { IMU_DISCONNECTED, ACTION_PRINT_ERR, STATE_WAIT_RECONNECT }
};

static const Transition t_reconnect[] = {
    { IMU_OK,           ACTION_NONE, STATE_READ },
    { IMU_DISCONNECTED, ACTION_WAIT, STATE_WAIT_RECONNECT },
    { IMU_ERROR,        ACTION_PRINT_ERR, STATE_RESET }
};

static void ExecuteAction(Action action)
{
    switch (action)
    {
        case ACTION_PRINT_DATA:
            PrintDeviceData(&data);
            break;

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
}

static void ProcessTransition(imu_status_t event,
                              const Transition *table,
                              int count)
{
    for (int i = 0; i < count; i++)
    {
        if (table[i].event == event)
        {
            ExecuteAction(table[i].action);
            state = table[i].nextState;
            return;
        }
    }

    message("Unhandled IMU event");
}

static void HandleInit(void)
{
    ProcessTransition(IMU_Init(), t_init, ARRAY_SIZE(t_init));
}

static void HandleRead(void)
{
    ProcessTransition(IMU_ReadData(&data), t_read, ARRAY_SIZE(t_read));
}

static void HandleReset(void)
{
    ProcessTransition(IMU_Reset(), t_reset, ARRAY_SIZE(t_reset));
}

static void HandleReconnect(void)
{
    ProcessTransition(IMU_Init(), t_reconnect, ARRAY_SIZE(t_reconnect));
}

void IMUManager_Init(void)
{
    state = STATE_INIT;
}

void IMUManager_Run(void)
{
    switch (state)
    {
        case STATE_INIT:
            HandleInit();
            break;

        case STATE_READ:
            HandleRead();
            break;

        case STATE_RESET:
            HandleReset();
            break;

        case STATE_WAIT_RECONNECT:
            HandleReconnect();
            break;

        default:
            break;
    }
}