```markdown
# IMU State Machine Design

## Overview

The application is implemented as a table-driven finite state machine that manages the complete lifecycle of the IMU. Instead of using long chains of conditional statements, each state has an associated transition table that maps every possible driver return value (event) to an action and the next state. This approach separates the state transition logic from the application logic, making the code modular, easier to read, and simple to extend.

## Implementation

To use this state machine in another project, replace the IMU driver calls (`IMU_Init()`, `IMU_ReadData()`, and `IMU_Reset()`) with the equivalent functions provided by the target device's driver. Update the transition tables so that the events correspond to the new driver's return values while keeping the same state machine structure. Platform-specific functionality such as logging, delays, and data output is isolated in the utility module (`utils.c`/`utils.h`), allowing it to be adapted to different operating systems or embedded platforms without modifying the state machine itself. Finally, call `IMUManager_Init()` once during system startup and repeatedly call `IMUManager_Run()` from the application's main loop or an RTOS task to continuously manage the device.

## States Used

The application consists of four states:

- **STATE_INIT** – Initializes the IMU before any sensor data is read.
- **STATE_READ** – Reads and displays IMU data during normal operation.
- **STATE_RESET** – Attempts to recover from initialization or communication failures by resetting the IMU.
- **STATE_WAIT_RECONNECT** – Waits for the IMU to reconnect after a disconnection and periodically attempts reinitialization.

Each state has its own transition table containing all valid events, the action to perform, and the next state.

## State Transitions

The application changes state according to the return value of the IMU driver APIs.

### STATE_INIT

- `IMU_OK` → Transition to **STATE_READ**
- `IMU_ERROR` → Transition to **STATE_RESET**
- `IMU_DISCONNECTED` → Transition to **STATE_WAIT_RECONNECT**

### STATE_READ

- `IMU_OK` → Remain in **STATE_READ** and print sensor data.
- `IMU_NO_NEW_DATA` → Wait briefly and remain in **STATE_READ**.
- `IMU_ERROR` → Transition to **STATE_RESET**.
- `IMU_DISCONNECTED` → Transition to **STATE_WAIT_RECONNECT**.
- `IMU_NOT_INITIALIZED` → Transition to **STATE_INIT**.

### STATE_RESET

- `IMU_OK` → Transition to **STATE_READ**.
- `IMU_ERROR` → Remain in **STATE_RESET** and retry recovery.
- `IMU_DISCONNECTED` → Transition to **STATE_WAIT_RECONNECT**.

### STATE_WAIT_RECONNECT

- `IMU_OK` → Transition to **STATE_READ** after successful reinitialization.
- `IMU_DISCONNECTED` → Wait and continue attempting reconnection.
- `IMU_ERROR` → Transition to **STATE_RESET**.

## Failure Handling

The application checks the return value of every IMU driver API call and never assumes that an operation succeeds. Initialization failures and communication errors cause the application to enter the reset state, where it repeatedly attempts recovery. If the IMU is disconnected, the application transitions to a dedicated reconnect state and periodically retries initialization until the sensor becomes available again. When no new sensor data is available, the application performs a short wait before retrying the read operation. This ensures the application remains responsive, avoids getting permanently stuck, and automatically resumes normal operation whenever the IMU recovers.

## Limitations

- The current implementation is designed for a single device instance.
- It relies on blocking driver APIs, so execution pauses while initialization and read operations complete.
- The transition tables must be updated if the target driver's return values differ from those used by the IMU driver.
- Although the state machine is reusable, the data output function (`PrintDeviceData()`) must be adapted to match the data structure of the target device.
```
