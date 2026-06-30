# Module 4 – Introduction to State Machines

## Objective

In this module, you will design an application that manages a simulated hardware device using a **Finite State Machine (FSM)**.

The goal is not to write a perfect solution on the first attempt. Instead, the goal is to think about how software should behave when the outside world changes unexpectedly.

---

# What is a State Machine?

A state machine is a way of organizing software where the system can be in **only one state at a time**.

Examples of states are:

* OFF
* INITIALIZING
* READY
* RUNNING
* ERROR

As different events occur, the system transitions from one state to another.

A simple example is shown below.

```
OFF
 │
 ▼
READY
 │
 ▼
RUNNING
 │
 ▼
ERROR
 │
 ▼
READY
```

At any instant, the system exists in only one of these states.

---

# Why Do We Use State Machines?

Many embedded systems do not execute the same logic forever.

Instead, their behavior changes depending on:

* Hardware status
* User input
* Sensor availability
* Communication status
* Errors
* Timeouts

A state machine allows these behaviors to be expressed in a clean and organized manner.

---

# Real-World Example

Imagine a robot with an IMU connected over I²C.

Normally the IMU works correctly and continuously provides orientation data.

Now imagine one of the following situations:

* The IMU cable is unplugged.
* The IMU fails during initialization.
* The IMU suddenly stops responding.
* The IMU begins working again after being reset.

Your application should be able to react appropriately without crashing or becoming stuck.

Although this module uses a simulated IMU running on a PC, these situations are common when working with real embedded hardware.

