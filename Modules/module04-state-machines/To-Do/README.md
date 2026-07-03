# Module 4 – Assignment

## Problem Statement

You have been provided with a simulated IMU driver (`imu.c` and `imu.h`).

Your task is to design an application that uses this driver to manage the complete lifecycle of the IMU.

The driver should be treated as a third-party library. **Do not modify any code inside `imu.c` or `imu.h`.**

Your solution should be written in your own application files.

---

# Objective

Design a robust application that is capable of:

* Initializing the IMU.
* Reading sensor data.
* Handling failures gracefully.
* Recovering from failures whenever possible.
* Continuing normal operation after recovery.

The focus of this assignment is **application design**, not driver development.

---

# Requirements

Your application must:

* Initialize the IMU before attempting to read data.
* Read and display IMU data when available.
* Correctly handle all return values provided by the driver.
* Avoid crashing or becoming permanently stuck due to driver failures.
* Produce clear and readable output that demonstrates the application's current behaviour.

---

# Driver Behaviour

The driver may exhibit one or more of the following behaviours during execution:

* Successful initialization
* Initialization failure
* Communication failure
* Sensor disconnection
* Sensor reconnection
* Temporary absence of new sensor data

Your application should behave correctly regardless of which of these situations occurs.

---

# Constraints

* Do **not** modify `imu.c`.
* Do **not** modify `imu.h`.
* Do **not** assume that every driver call succeeds.
* Keep your solution modular and easy to understand.

---

# Deliverables

Submit the following:

* Source code
* A short document (maximum one page) describing:

  * The states used in your application.
  * The events that cause transitions between states.
  * How your application responds to failures.

---

# Evaluation Criteria

Your submission will be evaluated based on:

* Correctness
* Robustness
* Code organization
* Readability
* Error handling
* Recovery behaviour

Your application will be tested using multiple driver behaviours. It should continue to behave correctly under different operating conditions.

---

# Hint

Think carefully about how the behaviour of your application changes over time.

Rather than writing one long sequence of code, consider how the application should react as different events occur during execution.
