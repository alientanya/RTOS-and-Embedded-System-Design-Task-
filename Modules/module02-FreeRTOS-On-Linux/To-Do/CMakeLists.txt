cmake_minimum_required(VERSION 3.15)

project(StudentSubmission C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# -------------------------------------------------
# FreeRTOS Configuration
# -------------------------------------------------

set(FREERTOS_PORT GCC_POSIX CACHE STRING "")
set(FREERTOS_HEAP 4 CACHE STRING "")

# -------------------------------------------------
# NPC Folder to Build
# -------------------------------------------------

set(NPC "Tanya" CACHE STRING "NPC folder to build")

# -------------------------------------------------
# Repository Root
# -------------------------------------------------

get_filename_component(
    REPO_ROOT
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../..
    ABSOLUTE
)

# -------------------------------------------------
# FreeRTOS Configuration
# -------------------------------------------------

add_library(freertos_config INTERFACE)

target_include_directories(freertos_config
    INTERFACE
        ${REPO_ROOT}/include
)

target_compile_definitions(freertos_config
    INTERFACE
        projCOVERAGE_TEST=0
)

# -------------------------------------------------
# FreeRTOS Kernel
# -------------------------------------------------

add_subdirectory(
    ${REPO_ROOT}/FreeRTOS-Kernel
    FreeRTOS-Kernel
)

# -------------------------------------------------
# Collect Source Files
# -------------------------------------------------

file(GLOB MODULE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/${NPC}/*.c"
)

# -------------------------------------------------
# Build Executable
# -------------------------------------------------

add_executable(app
    ${MODULE_SOURCES}
)

target_include_directories(app
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/${NPC}
        ${REPO_ROOT}/include
)

target_link_libraries(app
    PRIVATE
        freertos_kernel
        pthread
)