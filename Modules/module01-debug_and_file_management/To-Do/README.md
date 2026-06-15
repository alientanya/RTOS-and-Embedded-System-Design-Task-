# Module 01 Task - Driver Abstraction and Debugging

## Objective

In embedded systems, application code should not directly interact with microcontroller hardware.

Instead, hardware access should be hidden behind driver interfaces.

This allows the application code to remain portable even if the underlying microcontroller changes.

Your task is to design a simple driver layer on top of the provided Fake MCU API.

---

# Problem Statement

You have been provided with a Fake MCU implementation that simulates hardware peripherals.

The Fake MCU exposes the following functions:

```c
MCU_Init();
MCU_ReadADC();
MCU_ReadBatteryVoltage();
MCU_ReadStatusRegister();
```

Your task is to create a software architecture that prevents the application layer from directly calling these MCU functions.

Create the following files:

```text
sensor.h
sensor.c

battery.h
battery.c
```

These files should act as device drivers.

The application layer should only interact with your driver functions.

---

# Requirements

## Sensor Driver

Create a sensor driver that provides an interface for reading sensor data.

Example:

```c
int Sensor_Read(void);
```

The implementation should internally use:

```c
MCU_ReadADC();
```

---

## Battery Driver

Create a battery driver that provides an interface for reading battery voltage.

Example:

```c
int Battery_ReadVoltage(void);
```

The implementation should internally use:

```c
MCU_ReadBatteryVoltage();
```

---

## Application Layer

Create a main application that periodically reads:

* Sensor data
* Battery voltage

and prints the results.

Example:

```text
Sensor Value : 154
Battery      : 3890 mV
```

The values should continuously change because the Fake MCU generates new values on every read.

---

# Important Rules

The application layer must not directly call:

```c
MCU_ReadADC();
MCU_ReadBatteryVoltage();
MCU_ReadStatusRegister();
```

The application layer must only use the interfaces provided by:

```c
sensor.c
battery.c
```


The application layer must not include:

```c
fake_mcu.h
```

directly in any application source file.

Any solution that introduces a direct dependency between the application layer and the fake MCU layer will be considered a violation of the abstraction requirements.

The goal is to ensure that the application remains independent of the underlying hardware implementation.

---

# Architecture

The software should follow the structure below:

```text
+----------------------+
|   Application Layer  |
|       main.c         |
+----------+-----------+
           |
           v
+----------------------+
|     Driver Layer     |
| sensor.c battery.c   |
+----------+-----------+
           |
           v
+----------------------+
|      Fake MCU        |
|      fake_mcu.c      |
+----------------------+
```

---

# Why Are We Doing This?

In real embedded systems, applications are rarely written directly against hardware registers.

Instead, a driver layer isolates hardware-specific code from application logic.

This provides:

* Better portability
* Easier maintenance
* Easier testing
* Cleaner architecture

If the hardware changes in the future:

```text
STM32
ESP32
RISC-V
Linux Device
```

the application code should ideally remain unchanged.

Only the driver and hardware layers should require modification.

---

# Debugging Task

After implementing the driver layer:

1. Build the application.
2. Run the application.
3. Use GDB to inspect program execution.
4. Verify that:

   * Sensor values originate from the Sensor Driver.
   * Battery values originate from the Battery Driver.
   * The application never directly accesses the Fake MCU layer.

Use breakpoints and stepping commands to trace the flow:

```text
main()
   ↓
Sensor_Read()
   ↓
MCU_ReadADC()
```

and

```text
main()
   ↓
Battery_ReadVoltage()
   ↓
MCU_ReadBatteryVoltage()
```

---

# Provided Files

The following files are provided:

```text
fake_mcu.h
fake_mcu.c
```

Do not modify these files.

Your task is to build the driver layer on top of the provided MCU API.

---

# Expected Learning Outcomes

After completing this task, learners should understand:

* Layered software architecture
* Driver abstraction
* Separation of application and hardware code
* Basic embedded software design
* Debugging multi-file projects using GDB
* Tracing execution across software layers

```
```




# Submitting Your Solution

After completing the task, submit your work through GitHub.

Your solution should contain the files you created:

```text
sensor.c
sensor.h

battery.c
battery.h
```

along with any modifications required to build and run the application.

---

## Step 1 - Fork the Repository

Create your own copy of the repository using GitHub's Fork feature.

```text
Original Repository
        ↓
     Fork
        ↓
Your GitHub Repository
```

---

## Step 2 - Clone Your Fork

Clone your fork to your local machine.

Example:

```bash
git clone <your-fork-url>
```

---

## Step 3 - Create Your Solution

Navigate to the Module 01 task directory and add your files.

Example:

```text
Module01/
│
├── fake_mcu.c
├── fake_mcu.h
│
├── sensor.c
├── sensor.h
│
├── battery.c
├── battery.h
│
└── main.c
```

---

## Step 4 - Commit Your Changes

Add your files to Git.

```bash
git add .
```

Create a commit.

```bash
git commit -m "Completed Module01 driver abstraction task"
```

---

## Step 5 - Push Your Changes

Push the solution to your fork.

```bash
git push origin main
```

or

```bash
git push origin <branch-name>
```

depending on your workflow.

---

## Step 6 - Open a Pull Request

From GitHub:

1. Open your fork.
2. Click **Pull Request**.
3. Compare your changes against the original repository.
4. Create a Pull Request.

The Pull Request should include:

* Your driver implementation
* Any build changes
* A short explanation of your design

Example:

```text
Implemented Sensor Driver
Implemented Battery Driver
Application no longer directly accesses MCU functions
Verified functionality using GDB
```

---

## Learning Goal

This exercise introduces a simplified version of a professional software workflow:

```text
Write Code
    ↓
Build
    ↓
Run
    ↓
Debug
    ↓
Commit
    ↓
Push
    ↓
Create Pull Request
```

This workflow will be used throughout future modules and mirrors how many professional software and embedded teams collaborate on projects.
