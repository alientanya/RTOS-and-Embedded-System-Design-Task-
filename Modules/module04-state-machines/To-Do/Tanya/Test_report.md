# TEST_REPORT.md

# IMU State Machine Test Report

## Test 1 – Normal Operation

**Objective**

Verify that the application initializes the IMU successfully and continuously reads sensor data.

**Expected Behaviour**

- IMU initializes successfully.
- Application transitions from `STATE_INIT` to `STATE_READ`.
- Roll, Pitch, and Yaw values are printed continuously.
- No unexpected state transitions occur.

**Actual Behaviour**

- The IMU initialized successfully.
- The application remained in `STATE_READ`.
- Sensor values increased continuously and were printed correctly.

**Result**

![Static Badge](https://img.shields.io/badge/PASS-%2373ff00)

**Observations**

The state machine behaved as expected during normal operation.

---

## Test 2 – Initialization Failure

**Objective**

Verify that the application handles IMU initialization failures correctly.

**Expected Behaviour**

- IMU initialization returns `IMU_ERROR`.
- Application transitions to `STATE_RESET`.
- The application repeatedly attempts recovery without crashing.

**Actual Behaviour**

- Initialization failed as expected.
- The application entered `STATE_RESET`.
- The state machine continuously retried initialization through the reset state.

**Result**

![Static Badge](https://img.shields.io/badge/PASS-%2373ff00)

**Observations**

The supplied driver never recovers from this test mode, so remaining in the reset state indefinitely is expected behaviour.

---

## Test 3 – Read Failure

**Objective**

Verify that communication failures during data reads are handled correctly.

**Expected Behaviour**

- A read operation returns `IMU_ERROR`.
- The application transitions to `STATE_RESET`.
- After a successful reset, normal reading resumes.

**Actual Behaviour**

- The application repeatedly transitioned:

```
STATE_READ
    ↓
STATE_RESET
    ↓
STATE_READ
```

- Reading resumed successfully after every reset until another read failure occurred.

**Result**

![Static Badge](https://img.shields.io/badge/PASS-%2373ff00)

**Observations**

The recovery mechanism correctly restored operation after each communication failure.

---

## Test 4 – No New Data

**Objective**

Verify that temporary absence of new sensor data is handled correctly.

**Expected Behaviour**

- Driver returns `IMU_NO_NEW_DATA`.
- Application remains in `STATE_READ`.
- No invalid sensor values are printed.
- No unnecessary reset occurs.

**Actual Behaviour**

- The application remained in `STATE_READ`.
- No sensor values were printed.
- No reset or recovery actions were triggered.

**Result**

![Static Badge](https://img.shields.io/badge/PASS-%2373ff00)

**Observations**

The application correctly distinguished between "no new data" and an actual failure.

---

## Test 5 – Sensor Disconnection

**Objective**

Verify that the application detects sensor disconnection and automatically recovers after reconnection.

**Expected Behaviour**

- Driver reports `IMU_DISCONNECTED`.
- Application enters `STATE_WAIT_RECONNECT`.
- The application periodically retries initialization.
- Normal operation resumes after reconnection.

**Actual Behaviour**

- After approximately 20 successful reads, the application entered `STATE_WAIT_RECONNECT`.
- Once the simulated IMU reconnected, the application returned to `STATE_READ`.
- Sensor data continued from where it left off.

**Result**

![Static Badge](https://img.shields.io/badge/PASS-%2373ff00)

**Observations**

The state machine correctly handled both disconnection and automatic recovery.

---

# Bugs or Unexpected Behaviour

No functional bugs were observed during testing.

One minor observation is that the application prints the generic message:

```
IMU operation failed
```

for different failure conditions (communication error and disconnection). More descriptive messages could make debugging easier.

---

# Suggested Improvements

- Introduce a configurable retry delay or exponential backoff during repeated recovery attempts to reduce unnecessary CPU usage.
- Add timeout or retry limits if permanent hardware failure needs to be reported to higher-level software.
- Extend the transition tables to support additional devices or future driver events without changing the overall state machine architecture.