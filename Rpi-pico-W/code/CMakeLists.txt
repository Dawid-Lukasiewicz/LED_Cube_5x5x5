cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)
project(test_project C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(FREERTOS_KERNEL_PATH "/home/dawid/Projekty/Inżynierka/LED_Cube_5x5x5/Rpi-pico-W/code/FreeRTOS-Kernel")

if (NOT FREERTOS_KERNEL_PATH AND NOT DEFINED ENV{FREERTOS_KERNEL_PATH})
    message("Skipping Pico W FreeRTOS examples as FREERTOS_KERNEL_PATH not defined")
else()
    include(FreeRTOS_Kernel_import.cmake)
endif()

pico_sdk_init()

add_executable(main
            main.cpp
            cube.cpp
            led.cpp
            numbers.cpp
            animations.cpp
            wifi.cpp
)

set_target_properties(main PROPERTIES PICO_BOARD pico_w)
target_compile_definitions(main PRIVATE PICO_BOARD_DEFINED=pico_wireless)

pico_enable_stdio_usb(main 0)
pico_enable_stdio_uart(main 1)
pico_add_extra_outputs(main)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_LIST_DIR} )
# target_link_libraries(main pico_cyw43_arch_lwip_threadsafe_background pico_stdlib)
target_link_libraries(main 
        pico_stdlib
        pico_cyw43_arch_lwip_sys_freertos
        pico_lwip_iperf
        FreeRTOS-Kernel-Heap4
        )