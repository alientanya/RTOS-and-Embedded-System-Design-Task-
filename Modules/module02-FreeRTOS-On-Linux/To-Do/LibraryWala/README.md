# FreeRTOS on Linux (POSIX Port) - Learning Notes

## Goal

Run real FreeRTOS tasks on Linux using the POSIX simulator port.

---

# 1. Project Structure

```text
freertos-learning/
│
├── main.c
├── CMakeLists.txt
├── include/
│   └── FreeRTOSConfig.h
│
├── build/
│
└── FreeRTOS-Kernel/
```

Clone the kernel:

```bash
git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git
```

---

# 2. Understanding the FreeRTOS Repository

Kernel root:

```bash
cd FreeRTOS-Kernel
ls
```

Important files:

```text
tasks.c          -> Task scheduler
queue.c          -> Queues
timers.c         -> Software timers
list.c           -> Internal lists
portable/        -> Port layer
include/         -> Public headers
```

---

# 3. Finding the POSIX Port

Search for POSIX port:

```bash
find . -type d | grep -i posix
```

Result:

```text
./portable/ThirdParty/GCC/Posix
```

Enter the port:

```bash
cd portable/ThirdParty/GCC/Posix
ls
```

Files:

```text
port.c
portmacro.h
utils/
```

These files adapt FreeRTOS to Linux.

---

# 4. How FreeRTOS Selects the Port

Search:

```bash
grep -n "GCC_POSIX" CMakeLists.txt
```

Inspect:

```bash
sed -n '210,260p' CMakeLists.txt
```

Important discovery:

```cmake
if(UNIX)
    set(FREERTOS_PORT GCC_POSIX)
endif()
```

Meaning:

```text
Linux
  ↓
GCC_POSIX port selected automatically
```

---

# 5. Exploring FreeRTOS Source

Find xTaskCreate:

```bash
grep -n "xTaskCreate" tasks.c
```

Inspect:

```bash
sed -n '1741,1775p' tasks.c
```

Important flow:

```text
xTaskCreate()
      ↓
prvCreateTask()
      ↓
prvAddNewTaskToReadyList()
```

Find implementation:

```bash
grep -n "prvCreateTask(" tasks.c
```

View code:

```bash
sed -n '1643,1715p' tasks.c
```

---

# 6. FreeRTOS Configuration

Find template configuration:

```bash
grep -n "FreeRTOSConfig.h" README.md
```

Template location:

```text
examples/template_configuration/FreeRTOSConfig.h
```

Copy template:

```bash
mkdir include

cp FreeRTOS-Kernel/examples/template_configuration/FreeRTOSConfig.h include/
```

---

# 7. Creating CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.15)

project(FreeRTOSLearning C)

add_library(freertos_config INTERFACE)

target_include_directories(
    freertos_config
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(FreeRTOS-Kernel)

add_executable(
    app
    main.c
    FreeRTOS-Kernel/portable/MemMang/heap_4.c
)

target_link_libraries(
    app
    freertos_kernel
)
```

---

# 8. Configure Build

Generate build files:

```bash
cmake -S . -B build
```

Expected:

```text
Auto-Detected Unix, setting FREERTOS_PORT=GCC_POSIX
```

---

# 9. Build Project

```bash
cd build

cmake --build .
```

Successful build:

```text
[100%] Built target app
```

---

# 10. Running the Application

Run:

```bash
./app
```

---

# 11. First Debugging Problem

Tasks were not running.

Added:

```c
printf("Starting scheduler...\n");

vTaskStartScheduler();

printf("Scheduler FAILED!\n");
```

Output:

```text
Starting scheduler...
```

Meaning:

```text
Scheduler entered successfully
```

---

# 12. Using GDB

Start:

```bash
gdb ./app
```

Run:

```gdb
run
```

Interrupt:

```text
Ctrl + C
```

Backtrace:

```gdb
bt
```

Observed:

```text
main()
vTaskStartScheduler()
xPortStartScheduler()
```

Meaning:

```text
Scheduler is running.
```

---

# 13. Checking Task Creation

Modified code:

```c
BaseType_t ret1;
BaseType_t ret2;

ret1 = xTaskCreate(...);

ret2 = xTaskCreate(...);

printf("ret1=%ld ret2=%ld\n",
       (long)ret1,
       (long)ret2);
```

Output:

```text
ret1=-1
ret2=-1
```

Meaning:

```text
Task creation failed.
```

---

# 14. Understanding Return Values

From tasks.c:

```text
pdPASS = 1

errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY = -1
```

Therefore:

```text
ret = -1
```

means:

```text
Memory allocation failed.
```

---

# 15. Heap Investigation

Check heap size:

```bash
grep -n "configTOTAL_HEAP_SIZE" include/FreeRTOSConfig.h
```

Check dynamic allocation:

```bash
grep -n "configSUPPORT_DYNAMIC_ALLOCATION" include/FreeRTOSConfig.h
```

Check heap source:

```bash
find FreeRTOS-Kernel -name "heap_*.c"
```

Selected:

```text
heap_4.c
```

---

# 16. Fixing Task Creation Failure

Original:

```c
xTaskCreate(
    SensorTask,
    "Sensor",
    1024,
    NULL,
    1,
    NULL);
```

Problem:

```text
Stack too large
Heap exhausted
```

Changed to:

```c
configMINIMAL_STACK_SIZE
```

Example:

```c
xTaskCreate(
    SensorTask,
    "Sensor",
    configMINIMAL_STACK_SIZE,
    NULL,
    1,
    NULL);
```

---

# 17. Successful Result

Output:

```text
ret1=1 ret2=1

Starting scheduler...

Sensor Task
Display Task
Sensor Task
Display Task
...
```

Meaning:

```text
Task creation succeeded
Scheduler running
Context switching working
vTaskDelay working
```

---

# Useful Linux Commands

Current directory:

```bash
pwd
```

List files:

```bash
ls
```

Search text:

```bash
grep -n "xTaskCreate" tasks.c
```

Show file lines:

```bash
sed -n '1741,1775p' tasks.c
```

Find files:

```bash
find . -name "*.c"
```

View file:

```bash
cat main.c
```

View with line numbers:

```bash
cat -n main.c
```

Open editor:

```bash
nano main.c
```

---

# GDB Commands

Start:

```bash
gdb ./app
```

Run:

```gdb
run
```

Interrupt:

```text
Ctrl+C
```

Backtrace:

```gdb
bt
```

Next line:

```gdb
next
```

Breakpoint:

```gdb
break main
```

Quit:

```gdb
quit
```

---

# Key Lessons

1. FreeRTOS tasks consume heap memory.
2. Stack size is critical.
3. xTaskCreate() returning -1 usually indicates allocation failure.
4. FreeRTOSConfig.h is supplied by the application.
5. POSIX port allows learning FreeRTOS on Linux before moving to STM32.
6. GDB is essential for debugging scheduler startup issues.
7. Reading FreeRTOS source code is practical and manageable using grep and sed.
8. FreeRTOS architecture:

```text
Application
    ↓
Kernel
    ↓
Port Layer
    ↓
Operating System / Hardware
```
