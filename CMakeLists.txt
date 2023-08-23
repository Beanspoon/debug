cmake_minimum_required(VERSION 3.27)
project(trace VERSION 0.1)
set(EXEC trace.elf)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)

add_executable(${EXEC})

add_subdirectory(src)
add_subdirectory(chipsets/nrf52832)
add_subdirectory(common)

target_compile_options(${EXEC} PRIVATE
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

target_link_options(${EXEC} PRIVATE
    -specs=nosys.specs
    -Wl,--print-memory-usage
    -Wl,-Map=flash.map
    -Wl,--gc-sections
    -Wl,-T ../link.ld)
