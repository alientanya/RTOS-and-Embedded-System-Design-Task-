#ifndef ENCODER_H
#define ENCODER_H

#include <stdbool.h>
#include <stdint.h>

/*==========================================================
 * Encoder Data
 *=========================================================*/

typedef struct
{
    int32_t left_count;
    int32_t right_count;

} encoder_data_t;

/*==========================================================
 * Encoder Status
 *=========================================================*/

typedef enum
{
    ENCODER_OK = 0,

    ENCODER_ERROR,

    ENCODER_DISCONNECTED,

    ENCODER_NOT_INITIALIZED,

    ENCODER_NO_NEW_DATA

} encoder_status_t;

/*==========================================================
 * Public API
 *=========================================================*/

/**
 * @brief Initialize the encoder driver.
 *
 * @return ENCODER_OK on success.
 * @return ENCODER_ERROR on failure.
 * @return ENCODER_DISCONNECTED if encoder is unavailable.
 */
encoder_status_t Encoder_Init(void);

/**
 * @brief Read the latest encoder counts.
 *
 * @param data Pointer to output structure.
 *
 * @return ENCODER_OK if new data is available.
 * @return ENCODER_NO_NEW_DATA if no new counts are available.
 * @return ENCODER_ERROR on driver failure.
 * @return ENCODER_NOT_INITIALIZED if Encoder_Init() has not completed.
 * @return ENCODER_DISCONNECTED if encoder is disconnected.
 */
encoder_status_t Encoder_ReadData(encoder_data_t *data);

/**
 * @brief Reset the encoder driver.
 *
 * @return ENCODER_OK on success.
 * @return ENCODER_DISCONNECTED if encoder is unavailable.
 */
encoder_status_t Encoder_Reset(void);

/**
 * @brief Check whether the encoder is connected.
 *
 * @return true if connected.
 * @return false otherwise.
 */
bool Encoder_IsConnected(void);

#endif