cmake_minimum_required(VERSION 3.15)

project(Module02 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# -----------------------------
# Tell FreeRTOS which port to use
# -----------------------------
set(FREERTOS_PORT GCC_POSIX CACHE STRING "")

# -----------------------------
# FreeRTOSConfig.h location
# -----------------------------
add_library(freertos_config INTERFACE)

target_include_directories(freertos_config
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(freertos_config
    INTERFACE
        projCOVERAGE_TEST=0
)

# -----------------------------
# Add FreeRTOS Kernel
# -----------------------------
add_subdirectory(
    /home/tanya/workspace/freertos-learning/FreeRTOS-Kernel
    FreeRTOS-Kernel
)

# -----------------------------
# Application
# -----------------------------
add_executable(app
    main.c
    sensor.c
    battery.c
    emergency.c
    system.c
    fake_mcu.c
)

target_include_directories(app
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(app
    PRIVATE
        freertos_kernel
        pthread
)
