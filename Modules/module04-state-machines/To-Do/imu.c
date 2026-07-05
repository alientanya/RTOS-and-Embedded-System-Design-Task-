#include "imu.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>

#define DISCONNECT_AFTER_READS   20
#define DISCONNECT_DURATION_SEC   3

static time_t disconnect_time = 0;

/*==========================================================
 * Test Configuration
 * Change these values while evaluating submissions.
 *=========================================================*/

typedef enum
{
    TEST_NORMAL,
    TEST_INIT_FAIL,
    TEST_READ_FAIL,
    TEST_DISCONNECT,
    TEST_NO_DATA
} imu_test_mode_t;

static imu_test_mode_t test_mode =  TEST_DISCONNECT;

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

/*==========================================================
 * Private Functions
 *=========================================================*/

static void GenerateFakeData(void)
{
    latest_data.roll += 0.5f;
    latest_data.pitch += 0.2f;
    latest_data.yaw += 1.0f;
}

static void UpdateInternalState(void)
{
    switch (test_mode)
    {
        case TEST_NORMAL:
            break;

    case TEST_DISCONNECT:

        if ((read_counter != 0) &&
            (read_counter % DISCONNECT_AFTER_READS == 0) &&
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

            /* Prevent immediately disconnecting again */
            read_counter++;
            }
         }

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
        return IMU_DISCONNECTED;

    if (initialized)
        return IMU_OK;

    imu_state = IMU_STATE_INITIALIZING;

    usleep(100000);

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
        return IMU_DISCONNECTED;

    if (!initialized)
        return IMU_NOT_INITIALIZED;

    if (imu_state == IMU_STATE_ERROR)
        return IMU_ERROR;

    if (test_mode == TEST_READ_FAIL)
    {
        imu_state = IMU_STATE_ERROR;
        return IMU_ERROR;
    }

    if (test_mode == TEST_NO_DATA)
    {
        return IMU_NO_NEW_DATA;
    }

    usleep(5000);

    GenerateFakeData();

    *data = latest_data;

    read_counter++;

    return IMU_OK;
}

imu_status_t IMU_Reset(void)
{
    UpdateInternalState();

    if (!IMU_IsConnected())
        return IMU_DISCONNECTED;

    initialized = false;
    imu_state = IMU_STATE_CONNECTED;

    return IMU_Init();
}