cmake_minimum_required(VERSION 3.17)

include(../pico-sdk/pico_sdk_init.cmake)

project(Visualiser)

pico_sdk_init()

add_executable(Visualiser main.cpp)

# Link with the pico stdlib
target_link_libraries(Visualiser pico_stdlib hardware_pwm)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(Visualiser)

# Enable USB serial
pico_enable_stdio_usb(Visualiser 1)
pico_enable_stdio_uart(Visualiser 0)