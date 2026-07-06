# Device Manager & Driver Architecture (Prototype v1)

## Purpose

This document describes the first version of the generic **Device
Manager** that will become part of the team's central firmware library.

The goal is **not** to build a fully generic FSM framework yet. Instead,
we want a reusable lifecycle manager that works for most embedded
devices while remaining simple enough for everyone on the team to
understand and contribute to.

------------------------------------------------------------------------

# Design Goals

-   Provide a common lifecycle for hardware drivers.
-   Standardize how drivers expose initialization, reading, and
    recovery.
-   Allow juniors to contribute reusable modules to the central library.
-   Keep the implementation simple for Version 1.
-   Leave room for future improvements without changing the public API.

------------------------------------------------------------------------

# Proposed Folder Structure

``` text
Library/
│
├── device_manager/
│   ├── device_manager.c
│   ├── device_manager.h
│   └── device_types.h
│
├── imu/
│   ├── imu.c
│   ├── imu.h
│   ├── imu_manager.c
│   └── imu_manager.h
│
├── gps/
│
├── encoder/
│
└── utils/
```

------------------------------------------------------------------------

# Standard Driver Interface

Every driver added to the library should implement the same basic API.

``` c
device_status_t Device_Init(void);
device_status_t Device_Read(void *data);
device_status_t Device_Reset(void);
```

Example for IMU:

``` c
device_status_t IMU_Init(void);
device_status_t IMU_Read(imu_data_t *data);
device_status_t IMU_Reset(void);
```

Example for GPS:

``` c
device_status_t GPS_Init(void);
device_status_t GPS_Read(gps_data_t *data);
device_status_t GPS_Reset(void);
```

This makes every driver predictable and easy to integrate.

------------------------------------------------------------------------

# Generic Device Status

All drivers return the same status type.

``` c
typedef enum
{
    DEVICE_OK,
    DEVICE_BUSY,
    DEVICE_ERROR,
    DEVICE_DISCONNECTED,
    DEVICE_NOT_INITIALIZED
} device_status_t;
```

The Device Manager only understands these generic lifecycle states.

------------------------------------------------------------------------

# Device-Specific Information

Device-specific information should **not** be added to
`device_status_t`.

Examples:

GPS:

``` c
gps_fix_t GPS_GetFixType(void);
```

IMU:

``` c
imu_calibration_t IMU_GetCalibrationState(void);
```

CAN:

``` c
can_bus_state_t CAN_GetBusState(void);
```

These remain inside the driver.

------------------------------------------------------------------------

# Device Manager Responsibilities

The Device Manager is responsible for:

-   Running the lifecycle state machine
-   Calling Init()
-   Calling Read()
-   Calling Reset()
-   Handling common recovery flow
-   Updating the current state

It should **not**:

-   Print debug messages
-   Perform delays
-   Know IMU/GPS/Encoder specific details
-   Contain device-specific logic

------------------------------------------------------------------------

# Driver Responsibilities

Drivers are responsible for:

-   Hardware communication
-   Register access
-   Returning a generic device_status_t
-   Exposing device-specific APIs when required

Drivers should not contain application logic.

------------------------------------------------------------------------

# State Machine

The initial common lifecycle is:

``` text
INIT
  |
  v
RUN
  |
  +----> ERROR ----> RESET
  |
  +----> DISCONNECTED ----> WAIT ----> INIT
```

Future devices may extend this if necessary, but this is the baseline
supported by the library.

------------------------------------------------------------------------

# Why Not a Fully Generic FSM?

A completely generic FSM engine is a larger project.

For Version 1 we prioritize:

-   Simplicity
-   Readability
-   Reusability
-   Fast integration into the central library

The public API should remain stable so the implementation can evolve
later.

------------------------------------------------------------------------

# Future Improvements

Potential enhancements for later versions:

-   Callback-based actions
-   Generic FSM engine
-   Non-blocking timers
-   Event queues
-   Hierarchical state machines
-   Configurable transition tables

These are intentionally deferred until the team is comfortable with
Version 1.

------------------------------------------------------------------------

# Coding Rules

Every new driver added to the library should follow these rules:

1.  Implement Init(), Read(), and Reset().
2.  Return device_status_t.
3.  Keep hardware logic inside the driver.
4.  Keep application logic outside the driver.
5.  Expose additional device-specific APIs only when necessary.
6.  Avoid printing and blocking delays inside the Device Manager.

------------------------------------------------------------------------

# Philosophy

The goal of the central library is not to hide complexity.

It is to **standardize common patterns** so that every team member
writes drivers with a consistent interface.

Consistency improves:

-   readability
-   maintainability
-   onboarding
-   code reuse
-   long-term scalability

Version 1 values a clean, understandable design over maximum
flexibility.
