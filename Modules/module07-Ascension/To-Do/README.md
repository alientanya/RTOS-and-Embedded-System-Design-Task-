# Module 07 - Ascension

## Objective

Develop a complete RTOS firmware application by applying every major concept learned throughout this course.

Unlike previous modules, this project does not focus on learning a new API.

Instead, the goal is to demonstrate the ability to design firmware that is modular, maintainable, scalable and suitable for integration into larger embedded systems.

There is intentionally no single correct solution.

Your engineering decisions will be reviewed.

---

# Project Overview

Your firmware should simulate a small robotics software stack.

The application will:

- Acquire sensor data.
- Estimate the current robot state.
- Communicate the estimated state to an external system.
- Log important system events.

The project should resemble firmware that could later be migrated to a real embedded target with minimal changes.

---

# Functional Requirements

Your application shall contain **exactly three RTOS tasks.**

## Task 1 — Data Acquisition

Responsibilities:

- Initialize all supplied drivers.
- Acquire IMU data.
- Acquire Encoder data.
- Package sensor information.
- Forward sensor data to the next stage.

The IMU shall be managed using a **State Machine**.

The Encoder driver does not require a State Machine.

---

## Task 2 — State Estimation

Responsibilities:

- Receive sensor data from the acquisition task.
- Estimate the current robot state.
- Forward the estimated state to the communication task.

The state estimation algorithm shall be isolated from the RTOS task.

Students shall implement the estimation algorithm inside a separate module.

Example:

```
state_estimation_task.c

        │

        ▼

algorithm.c

        │

        ▼

robot_state_t
```

The RTOS task should only be responsible for scheduling and data flow.

The algorithm module should contain the mathematical implementation.

Possible future algorithms include:

- Dead Reckoning
- Complementary Filter
- Extended Kalman Filter (EKF)
- Unscented Kalman Filter (UKF)
- Particle Filter
- Visual Odometry
- SLAM
- Sensor Fusion

For this project, a simple placeholder implementation is sufficient.

The architecture should allow the algorithm to be replaced without modifying the task.

---

## Task 3 — Communication

Responsibilities:

- Receive the latest robot state.
- Transmit the robot state through the platform interface.
- Perform periodic communication activities.
- Report communication events to the logger.

No actual communication protocol is required for this module.

Students shall design the task such that future communication protocols can be integrated without modifying the application.

Examples include:

- USB
- UART
- CAN
- Ethernet
- TCP/IP
- ROS2

The communication layer should expose a clean interface even if the implementation is initially empty.

The Logger may be invoked from this task to report communication events and transmitted data.

---

# RTOS Requirements

Your implementation must demonstrate the concepts covered throughout this course.

This includes:

- Tasks
- Queues
- State Machines
- Mutexes
- Semaphores
- Software Timers

The use of each feature should be justified through your system design.

---

# Platform Abstraction

A `platform.h` interface will be provided.

All platform dependent functionality shall be implemented through this interface.

Application modules must **not** directly call Linux specific functions.

Examples include:

- printf()
- usleep()
- clock_gettime()

Additional APIs may be added to `platform.h` if required.

Existing APIs must not be removed or modified.

---

# Logger

A Logger module shall be implemented.

The Logger shall be driven using a **Software Timer**.

The logger is responsible for reporting:

- State Machine transitions
- Driver errors
- Communication events
- Important system information

Avoid continuously printing raw sensor values from multiple tasks.

The Communication Task should be responsible for transmitting application data.

---

# Timestamping

Meaningful data should include timestamps wherever appropriate.

Timestamp information should remain associated with the data as it moves through the system.

---

# File Structure

The following files are expected as a minimum.

```
main.c

acquisition_task.c
acquisition_task.h

state_estimation_task.c
state_estimation_task.h

communication_task.c
communication_task.h

imu_state_machine.c
imu_state_machine.h

logger.c
logger.h

platform_linux.c
platform_linux.h
```

Students are free to introduce additional modules where appropriate.

---

# Documentation

Include a README describing:

- Overall architecture
- Task responsibilities
- Module responsibilities
- Synchronization strategy
- Design decisions
- Assumptions
- Future improvements
- Limitations

Explain **why** your architecture was chosen rather than simply describing the code.

---

# Evaluation

Submissions will be evaluated based on:

- Correctness
- Code Quality
- RTOS Usage
- Platform Abstraction
- Modularity
- Scalability
- Documentation
- Engineering Decisions

A working application is only one part of the evaluation.

The quality of the software architecture is equally important.