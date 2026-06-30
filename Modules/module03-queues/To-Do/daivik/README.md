# Module 03: FreeRTOS Producer-Consumer Architecture

## Overview
This project implements a thread-safe, multi-tasking Producer-Consumer system using FreeRTOS. It integrates the hardware abstraction drivers developed in Module 01 and runs them concurrently, utilizing FreeRTOS Queues to safely pass massive 512-byte sensor data structures between tasks without race conditions.

---

## 1. RTOS Component Verification & Safety
To ensure the RTOS boots and operates safely on limited hardware, strict verification checks are enforced at every initialization step:

* **Queue Creation Verification:** Before tasks are spun up, the system checks if `xQueueCreate()` returns `NULL`. If the 64KB heap is exhausted before the 10-slot queue is built, the system catches the failure and halts, preventing a silent hard fault.
* **Task Creation Verification:** The return values of `xTaskCreate()` are captured and evaluated against `pdPASS`. If the OS cannot allocate the required 256-word stack and Task Control Block (TCB) for either the Producer or Consumer, the initialization aborts.
* **Stack Overflow Trapping:** The `vApplicationStackOverflowHook` is enabled. If any task breaches its allocated stack boundary during execution, the OS immediately traps the error, prints the name of the offending task to the terminal, and freezes the system for debugging.

---

## 2. Heap Memory Diagnostics Strategy
**Design Choice:** Memory tracking is implemented via **Event-Driven Polling** inside the Consumer (`DisplayTask`) rather than spinning up a dedicated memory-tracking task.

**Justification:**
1. **Zero RAM Overhead:** Creating a dedicated `MemoryTrackerTask` would consume over 1 Kilobyte of heap memory (for its stack and TCB) just to monitor the heap. Appending the diagnostic to an existing task eliminates this waste.
2. **Console Safety (Thread-Safe UART):** By placing the memory diagnostic `printf` inside the `DisplayTask` (which already owns the terminal output), we prevent multiple tasks from fighting for the standard output and corrupting the terminal display.
3. **Strategic Timing:** The diagnostic checks `xPortGetFreeHeapSize()` at the exact moment the system is under the most stress—right after a 512-byte structure is pulled from the queue and processed. 

---

## 3. Limitations of the Diagnostic Solution
While highly efficient, this memory tracking approach has a few technical limitations:

* **No Per-Task Resolution:** `xPortGetFreeHeapSize()` only tracks the global heap. It does not tell us how much of a specific task's stack is being used. (Future improvement: Implement `uxTaskGetStackHighWaterMark()` to track individual task efficiency).
* **Blind to Fragmentation:** The current metric shows total free bytes, but does not indicate if those bytes are contiguous or fragmented. 
* **Execution Dependency:** Because the memory check is event-driven inside the `DisplayTask`, if the Producer stops sending data (or the queue blocks indefinitely), the memory diagnostic will stop updating on the console, blinding us to any background memory leaks.

---

## 4. System Architecture & Memory Management
This system is designed to run indefinitely without fatal memory degradation. 

* **Static Runtime Heap:** All dynamic allocations (Tasks and Queues) are performed upfront during `main()` before the scheduler starts. 
* **Copy-by-Value:** Data is passed through the queue using FreeRTOS's native copy-by-value mechanism. No `malloc()` or `free()` calls are made during the infinite `while(1)` execution loops. 
* **Leak Prevention:** Because the runtime execution does not dynamically allocate or destroy memory, the system is immune to runtime memory leaks and heap fragmentation, resulting in a static and predictable memory footprint during execution.

## Build and Run Instructions
```bash
# Generate the build environment
cmake -B build

# Compile the executable
cmake --build build

# Run the FreeRTOS Application
./build/app