# Simulated Drivers

## Overview

This project includes simulated drivers that behave similarly to real embedded peripherals.

The purpose of these drivers is to allow application development without requiring physical hardware.

For this module, the following drivers are provided:

- IMU Driver
- Encoder Driver

These drivers are considered **third-party libraries**.

Students **must not modify** the supplied driver source files.

---

# Philosophy

When developing embedded software, application engineers rarely write the device drivers themselves.

Instead, they receive a driver library and must design their application around the provided API.

This project follows the same approach.

Your application should communicate only through the public interfaces exposed by each driver.

---

# IMU Driver

## Purpose

The IMU driver simulates an Inertial Measurement Unit capable of producing:

- Roll
- Pitch
- Yaw

The driver can also simulate common hardware failures such as:

- Initialization failure
- Read failure
- Temporary disconnection
- No new data available

Your application is expected to correctly handle every possible return value.

---

## Public API

### Initialize

```c
imu_status_t IMU_Init(void);
```

Initializes the IMU.

Must be called before attempting to read data.

---

### Read Data

```c
imu_status_t IMU_ReadData(imu_data_t *data);
```

Reads the latest IMU sample.

Example

```c
imu_data_t imu;

if (IMU_ReadData(&imu) == IMU_OK)
{
    /* Process data */
}
```

---

### Reset

```c
imu_status_t IMU_Reset(void);
```

Attempts to recover the driver after an error.

---

### Connection Status

```c
bool IMU_IsConnected(void);
```

Returns whether the simulated IMU is currently connected.

---

# Encoder Driver

## Purpose

The encoder driver simulates wheel encoder counts.

Unlike the IMU, the encoder simply produces increasing count values.

It is intentionally kept simple because a hardware timer normally performs encoder counting automatically on an MCU.

---

## Public API

### Initialize

```c
encoder_status_t Encoder_Init(void);
```

Initializes the encoder.

---

### Read Data

```c
encoder_status_t Encoder_ReadData(encoder_data_t *data);
```

Reads the latest encoder counts.

Example

```c
encoder_data_t encoder;

if (Encoder_ReadData(&encoder) == ENCODER_OK)
{
    /* Process counts */
}
```

---

### Reset

```c
encoder_status_t Encoder_Reset(void);
```

Attempts to recover the encoder driver.

---

### Connection Status

```c
bool Encoder_IsConnected(void);
```

Returns whether the encoder is currently connected.

---

# Expected Usage

A typical application should follow this sequence.

```
Initialize Driver
        │
        ▼
Read Data
        │
        ▼
Handle Return Status
        │
        ▼
Process Data
        │
        ▼
Repeat
```

Applications should never assume that a read operation will always succeed.

Every return value should be handled appropriately.

---

# Important Notes

- Do not modify the supplied drivers.
- Do not access internal driver variables.
- Communicate only through the public API.
- Assume the drivers behave exactly like real hardware drivers.

---

# Testing

The supplied drivers contain internal test modes that simulate various hardware conditions.

These are intended to evaluate the robustness of your application.

Your application should continue operating correctly regardless of the simulated condition.

Successful firmware is expected to:

- Recover from temporary failures.
- Avoid crashing.
- Avoid becoming permanently stuck.
- Continue operating whenever recovery is possible.

---

# Future Compatibility

Although these drivers run on Linux today, the application should be written as if these were real hardware drivers.

A correctly designed application should require little or no modification when the simulated drivers are replaced with actual STM32 drivers.