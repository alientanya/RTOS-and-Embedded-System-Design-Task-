#include "encoder.h"
#include "Platform.h"

#include <stdbool.h>

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

} encoder_test_mode_t;

static encoder_test_mode_t test_mode = TEST_NORMAL;

/*==========================================================
 * Internal State
 *=========================================================*/

typedef enum
{
    ENCODER_STATE_DISCONNECTED,
    ENCODER_STATE_CONNECTED,
    ENCODER_STATE_READY,
    ENCODER_STATE_ERROR

} encoder_state_t;

static encoder_state_t state = ENCODER_STATE_CONNECTED;

static bool initialized = false;
static encoder_data_t encoder_data;

/*==========================================================
 * Public API
 *=========================================================*/

bool Encoder_IsConnected(void)
{
    return (state != ENCODER_STATE_DISCONNECTED);
}

encoder_status_t Encoder_Init(void)
{
    if (!Encoder_IsConnected())
    {
        return ENCODER_DISCONNECTED;
    }

    if (test_mode == TEST_INIT_FAIL)
    {
        state = ENCODER_STATE_ERROR;
        return ENCODER_ERROR;
    }

    initialized = true;
    state = ENCODER_STATE_READY;

    return ENCODER_OK;
}

encoder_status_t Encoder_ReadData(encoder_data_t *data)
{
    if (!Encoder_IsConnected())
    {
        return ENCODER_DISCONNECTED;
    }

    if (!initialized)
    {
        return ENCODER_NOT_INITIALIZED;
    }

    if (state == ENCODER_STATE_ERROR)
    {
        return ENCODER_ERROR;
    }

    if (test_mode == TEST_READ_FAIL)
    {
        state = ENCODER_STATE_ERROR;
        return ENCODER_ERROR;
    }

    if (test_mode == TEST_NO_DATA)
    {
        return ENCODER_NO_NEW_DATA;
    }

    encoder_data.left_count += 5;
    encoder_data.right_count += 5;

    *data = encoder_data;

    return ENCODER_OK;
}

encoder_status_t Encoder_Reset(void)
{
    if (!Encoder_IsConnected())
    {
        return ENCODER_DISCONNECTED;
    }

    initialized = false;
    state = ENCODER_STATE_CONNECTED;

    return Encoder_Init();
}