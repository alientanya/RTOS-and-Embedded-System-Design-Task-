#ifndef IMU_H
#define IMU_H

#include <stdbool.h>
#include <stdint.h>

/*==========================================================
 * IMU Data
 *=========================================================*/

typedef struct
{
    float roll;
    float pitch;
    float yaw;

} imu_data_t;

/*==========================================================
 * IMU Status
 *=========================================================*/

typedef enum
{
    IMU_OK = 0,

    IMU_ERROR,

    IMU_DISCONNECTED,

    IMU_NOT_INITIALIZED,

    IMU_NO_NEW_DATA

} imu_status_t;

/*==========================================================
 * Public API
 *=========================================================*/

/**
 * @brief Initialize the IMU.
 *
 * @return IMU_OK on success.
 * @return IMU_ERROR if initialization fails.
 * @return IMU_DISCONNECTED if no IMU is detected.
 */
imu_status_t IMU_Init(void);

/**
 * @brief Read the latest IMU data.
 *
 * @param data Pointer to output structure.
 *
 * @return IMU_OK if new data was read.
 * @return IMU_NO_NEW_DATA if no new sample is available.
 * @return IMU_ERROR on communication failure.
 * @return IMU_NOT_INITIALIZED if IMU_Init() has not completed.
 * @return IMU_DISCONNECTED if the IMU is disconnected.
 */
imu_status_t IMU_ReadData(imu_data_t *data);

/**
 * @brief Reset the IMU.
 *
 * @return IMU_OK if reset succeeds.
 * @return IMU_DISCONNECTED if the IMU is not connected.
 */
imu_status_t IMU_Reset(void);

/**
 * @brief Check whether the IMU is connected.
 *
 * @return true if connected.
 * @return false otherwise.
 */
bool IMU_IsConnected(void);

#endif /* IMU_H */