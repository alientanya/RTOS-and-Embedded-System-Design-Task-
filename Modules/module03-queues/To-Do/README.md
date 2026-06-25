# Module 03 - FreeRTOS Queues

## Learning Objectives

After completing this module, learners should understand:

* Creating FreeRTOS queues
* Sending data between tasks
* Receiving data from queues
* Blocking on queue operations
* Basic producer-consumer architecture

---

## Objective

The objective of this exercise is to transfer data between two FreeRTOS tasks using a queue.

You are provided with a sensor module that generates sensor data.

Your task is to create two FreeRTOS tasks and use a queue to transfer sensor data from one task to another.

---

## Provided Files

The following files are provided:

```text
sensor.c
sensor.h
```

Do not modify the sensor module.

---

## Sensor Interface

The sensor module exposes the following API:

```c
Sensor_Init();
```

Initializes the sensor module.

```c
Sensor_Read();
```

Returns a sensor data structure.

Refer to `sensor.h` for the exact structure definition.

---

## Problem Statement

Create a FreeRTOS application consisting of two tasks.

### SensorTask

This task is responsible for:

1. Reading sensor data using:

```c
Sensor_Read();
```

2. Sending the sensor data to a queue.

The task should execute periodically.

---

### DisplayTask

This task is responsible for:

1. Receiving sensor data from the queue.
2. Displaying the received information using:

```c
printf();
```

The task should wait for new data using FreeRTOS queue APIs.

---

## Required Architecture

```text
+------------------+
|    SensorTask    |
+---------+--------+
          |
          | Queue
          |
          v
+------------------+
|   DisplayTask    |
+------------------+
```

---

## Requirements

Create:

```text
SensorTask
DisplayTask
```

Create:

```text
One FreeRTOS Queue
```

Use the queue to transfer sensor data from `SensorTask` to `DisplayTask`.

The application must use FreeRTOS APIs.


When implementing applications using FreeRTOS, embedded developers must satisfy both **functional** and **resource** requirements.

For this module, keep the following design goals in mind:

* Use the minimum practical RAM required by your application.
* Allocate only as much task stack as necessary for each task.
* Choose queue depth of "10" so 10 sensor values can be carried by queue max.
* Remember that queues store copies of the data being sent.

Throughout this module, consider how design decisions such as task stack size, queue depth, and message size affect the total RAM usage of the system.


---

## Restrictions

Do not use:

```c
sleep()
usleep()
```

Use FreeRTOS timing functions instead.

Example:

```c
vTaskDelay();
```

---

## Expected Behaviour

The application should continuously:

1. Read sensor data.
2. Send sensor data through a queue.
3. Receive sensor data in another task.
4. Display the received data using `printf()`.

Example:

```text
Sensor ID: 1
Timestamp: 0

Sensor ID: 1
Timestamp: 1

Sensor ID: 1
Timestamp: 2
```

The exact output may vary depending on your implementation.

---

## Submission

Submit your solution through GitHub.

### Step 1

Fork the repository.

### Step 2

Clone your fork.

### Step 3

Implement the required queue-based communication.

### Step 4

Commit your changes.

```bash
git add .
git commit -m "Completed Module03 Queue Task"
```

### Step 5

Push your changes.

```bash
git push origin main
```

### Step 6

Create a Pull Request.

The Pull Request should include:

```text
Implemented SensorTask
Implemented DisplayTask
Implemented Queue Communication
Verified Data Transfer
```

---

## Learning Goal

This exercise introduces the basic workflow for inter-task communication using FreeRTOS queues.

```text
Create Queue
      ↓
Create Producer Task
      ↓
Create Consumer Task
      ↓
Transfer Data
      ↓
Observe Behaviour
      ↓
Debug
```
