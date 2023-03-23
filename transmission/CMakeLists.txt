cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(transmission_code C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(transmission
    gpsProcessing.cpp
)

pico_enable_stdio_usb(transmission 1)
pico_enable_stdio_uart(transmission 1)

pico_add_extra_outputs(transmission)

target_link_libraries(transmission pico_stdlib hardware_uart)