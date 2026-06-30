# Fake IMU Driver Documentation

## Overview

This module provides a simulated IMU (Inertial Measurement Unit) driver for use in this assignment.

The driver is intended to mimic the behaviour of a real embedded sensor while running entirely on a desktop computer.

You should treat this module as if it were a third-party driver provided by a hardware vendor.

> **Do not modify `imu.c` or `imu.h`.**

> **Do not open and look inside `imu.c`.**

Your application should interact with the driver only through the public APIs described below.

---

# Public API

## `imu_status_t IMU_Init(void)`

Initializes the IMU.

### Returns

| Status             | Description                            |
| ------------------ | -------------------------------------- |
| `IMU_OK`           | Initialization completed successfully. |
| `IMU_ERROR`        | Initialization failed.                 |
| `IMU_DISCONNECTED` | No IMU is connected.                   |

### Timing

This function simulates sensor initialization and blocks for approximately **100 ms** before returning.

---

## `imu_status_t IMU_ReadData(imu_data_t *data)`

Reads the latest IMU sample.

### Parameters

`data`

Pointer to an `imu_data_t` structure that will receive the latest sensor values.

### Returns

| Status                | Description                                        |
| --------------------- | -------------------------------------------------- |
| `IMU_OK`              | New sensor data has been returned.                 |
| `IMU_ERROR`           | A communication error occurred while reading data. |
| `IMU_NOT_INITIALIZED` | The IMU has not been initialized.                  |
| `IMU_DISCONNECTED`    | The IMU is disconnected.                           |
| `IMU_NO_NEW_DATA`     | No new sensor data is currently available.         |

### Timing

This function simulates an I²C communication transaction and blocks for approximately **5 ms** before returning.

---

## `imu_status_t IMU_Reset(void)`

Resets the IMU.

A successful reset clears the current initialization state.

The IMU must be initialized again before new data can be read.

### Returns

| Status             | Description                   |
| ------------------ | ----------------------------- |
| `IMU_OK`           | Reset completed successfully. |
| `IMU_DISCONNECTED` | The IMU is disconnected.      |

---

## `bool IMU_IsConnected(void)`

Checks whether an IMU is currently connected.

### Returns

`true`

The IMU is connected.

`false`

The IMU is not connected.

---

# Typical Usage

The following example demonstrates the normal usage of the driver.

```c
imu_data_t imuData;

if (IMU_Init() != IMU_OK)
{
    /* Handle initialization failure */
}

while (1)
{
    if (IMU_ReadData(&imuData) == IMU_OK)
    {
        /* Process sensor data */
    }
}
```

This example demonstrates only the basic use of the API.

---

# Notes

* The IMU may not always initialize successfully.
* The IMU may become unavailable.
* Read operations may fail.
* New sensor data may not always be available.
* Your application should handle these situations appropriately.

Do not assume that every API call will always succeed.

---

# Implementation Notes

The delays used by this driver are intentionally exaggerated to simulate hardware behaviour and make timing effects easier to observe during testing.

| Operation      | Simulated Delay |
| -------------- | --------------: |
| Initialization |          100 ms |
| Data Read      |            5 ms |

These delays are part of the simulation and do not represent the performance of any specific IMU.
