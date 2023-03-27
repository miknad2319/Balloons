cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(receiver_code C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(receiver
    Receiver.cpp
)

pico_enable_stdio_usb(receiver 1)
pico_enable_stdio_uart(receiver 1)

pico_add_extra_outputs(receiver)

target_link_libraries(receiver pico_stdlib hardware_uart)