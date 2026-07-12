#include "imu.h"
#include "Platform.h"

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define DISCONNECT_AFTER_READS   20
#define DISCONNECT_DURATION_SEC   3

/*==========================================================
 * Test Configuration
 *=========================================================*/

typedef enum
{
    TEST_NORMAL,
    TEST_INIT_FAIL,
    TEST_READ_FAIL,
    TEST_DISCONNECT,
    TEST_NO_DATA
} imu_test_mode_t;

static imu_test_mode_t test_mode = TEST_DISCONNECT;

/*==========================================================
 * Internal State
 *=========================================================*/

typedef enum
{
    IMU_STATE_DISCONNECTED,
    IMU_STATE_CONNECTED,
    IMU_STATE_INITIALIZING,
    IMU_STATE_READY,
    IMU_STATE_ERROR
} imu_internal_state_t;

static imu_internal_state_t imu_state = IMU_STATE_CONNECTED;

static bool initialized = false;
static imu_data_t latest_data;

static uint32_t read_counter = 0;
static time_t disconnect_time = 0;

/*==========================================================
 * Private Functions
 *=========================================================*/

static void GenerateFakeData(void)
{
    latest_data.roll  += 0.5f;
    latest_data.pitch += 0.2f;
    latest_data.yaw   += 1.0f;
}

static void UpdateInternalState(void)
{
    switch (test_mode)
    {
        case TEST_NORMAL:
            break;

        case TEST_DISCONNECT:

            if ((read_counter != 0U) &&
                ((read_counter % DISCONNECT_AFTER_READS) == 0U) &&
                (imu_state != IMU_STATE_DISCONNECTED))
            {
                imu_state = IMU_STATE_DISCONNECTED;
                disconnect_time = time(NULL);
            }

            if (imu_state == IMU_STATE_DISCONNECTED)
            {
                if ((time(NULL) - disconnect_time) >= DISCONNECT_DURATION_SEC)
                {
                    imu_state = IMU_STATE_CONNECTED;

                    /* Prevent immediate disconnection after reconnect */
                    read_counter++;
                }
            }

            break;

        default:
            break;
    }
}

/*==========================================================
 * Public API
 *=========================================================*/

bool IMU_IsConnected(void)
{
    return (imu_state != IMU_STATE_DISCONNECTED);
}

imu_status_t IMU_Init(void)
{
    UpdateInternalState();

    if (!IMU_IsConnected())
    {
        return IMU_DISCONNECTED;
    }

    if (initialized)
    {
        return IMU_OK;
    }

    imu_state = IMU_STATE_INITIALIZING;

    Platform_DelayMs(100);

    if (test_mode == TEST_INIT_FAIL)
    {
        imu_state = IMU_STATE_ERROR;
        return IMU_ERROR;
    }

    initialized = true;
    imu_state = IMU_STATE_READY;

    return IMU_OK;
}

imu_status_t IMU_ReadData(imu_data_t *data)
{
    UpdateInternalState();

    if (!IMU_IsConnected())
    {
        return IMU_DISCONNECTED;
    }

    if (!initialized)
    {
        return IMU_NOT_INITIALIZED;
    }

    if (imu_state == IMU_STATE_ERROR)
    {
        return IMU_ERROR;
    }

    if (test_mode == TEST_READ_FAIL)
    {
        imu_state = IMU_STATE_ERROR;
        return IMU_ERROR;
    }

    if (test_mode == TEST_NO_DATA)
    {
        return IMU_NO_NEW_DATA;
    }

    Platform_DelayMs(5);

    GenerateFakeData();

    *data = latest_data;

    read_counter++;

    return IMU_OK;
}

imu_status_t IMU_Reset(void)
{
    UpdateInternalState();

    if (!IMU_IsConnected())
    {
        return IMU_DISCONNECTED;
    }

    initialized = false;
    imu_state = IMU_STATE_CONNECTED;
    disconnect_time = 0;

    return IMU_Init();
}