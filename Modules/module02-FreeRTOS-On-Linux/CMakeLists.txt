cmake_minimum_required(VERSION 3.15)
project(FreeRTOS_Safety_System C)

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
    sensor.c
    battery.c
    emergency.c
    system.c
    fake_mcu.c
    FreeRTOS-Kernel/portable/MemMang/heap_4.c
)
target_link_libraries(
    app
    freertos_kernel
)