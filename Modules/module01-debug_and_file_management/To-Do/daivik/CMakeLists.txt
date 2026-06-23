cmake_minimum_required(VERSION 3.15)
project(Daivik_Module01 C)

# Tell the compiler to look one folder up (..) to find fake_mcu.h
include_directories(..)

# Build the app using your files + the senior's hardware file
add_executable(app 
    main.c 
    sensor.c 
    battery.c 
    system.c
    ../fake_mcu.c
)