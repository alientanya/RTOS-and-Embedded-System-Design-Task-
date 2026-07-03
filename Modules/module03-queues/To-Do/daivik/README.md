## 1. RTOS Safety Checks

* **Queue Check:** Verify `xQueueCreate()` does not return `NULL`. Stop the system if queue creation fails.
* **Task Check:** Verify `xTaskCreate()` returns `pdPASS` before starting the scheduler.
* **Stack Overflow:** Enable `vApplicationStackOverflowHook()` to detect stack overflows, print the task name, and halt execution.

---

## 2. Heap Monitoring

**Design Choice:** Monitor heap usage inside the Consumer (`DisplayTask`) instead of using a separate task.

**Benefits:**

* Saves RAM by avoiding an extra task.
* Prevents multiple tasks from writing to the UART.
* Checks heap usage (`xPortGetFreeHeapSize()`) during normal data processing.

---

## 3. Limitations

* Reports only total free heap, not per-task stack usage.
* Does not detect heap fragmentation.
* Updates only when the Consumer task is running.

---

## 4. Memory Management

* All tasks and queues are created before the scheduler starts.
* Queue transfers data by value; no `malloc()` or `free()` is used during runtime.
* Fixed memory allocation prevents runtime memory leaks and keeps memory usage predictable.
