cmake_minimum_required(VERSION 3.15)

project(Module02 C)

set(CMAKE_C_STANDARD 11)

# Use the POSIX port of FreeRTOS
set(FREERTOS_PORT GCC_POSIX CACHE STRING "")
set(FREERTOS_HEAP 4 CACHE STRING "")

# Location of FreeRTOSConfig.h
add_library(freertos_config INTERFACE)

target_include_directories(freertos_config
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(freertos_config
    INTERFACE
        projCOVERAGE_TEST=0
)

# Add the FreeRTOS kernel
add_subdirectory(
    /home/tanya/workspace/freertos-learning/FreeRTOS-Kernel
    FreeRTOS-Kernel
)

# Create executable
add_executable(app
    main.c
    sensor.c
    battery.c
    emergency.c
    system.c
    fake_mcu.c
)

target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(app
    PRIVATE
        freertos_kernel
        pthread
)