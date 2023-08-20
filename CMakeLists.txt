cmake_minimum_required(VERSION 3.27)
project(trace VERSION 0.1)
set(EXECUTABLE trace.elf)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)

add_executable(EXECUTABLE main.c)

#add_subdirectory(boards)

target_compile_options(EXECUTABLE PRIVATE
    -mthumb
    -mcpu=cortex-m4
    -std=c99
    -Og
    -g
    -ffreestanding
    -ffunction-sections
    -fdata-sections
    -Wall
    -Wextra)

target_link_options(EXECUTABLE PRIVATE
    -specs=nosys.specs
    -Wl,--print-memory-usage
    -Wl,-Map=flash.map
    -Wl,--gc-sections
    -Wl,-T ../link.ld)
