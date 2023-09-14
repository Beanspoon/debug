cmake_minimum_required(VERSION 3.27)
project(trace VERSION 0.1)
set(EXEC trace.elf)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)

add_executable(${EXEC})

add_subdirectory(chipsets/${CHIPSET})
add_subdirectory(boards/${BOARD})
add_subdirectory(common)

target_include_directories(${EXEC} PRIVATE include)
file(GLOB HEADERS include/*.h)
target_sources(${EXEC} PRIVATE ${HEADERS}
    ${CMAKE_SOURCE_DIR}/link.ld
    src/main.c)

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
    -Wl,-T ${CMAKE_SOURCE_DIR}/link.ld)

add_custom_command(
    TARGET ${EXEC}
    POST_BUILD
    COMMAND arm-none-eabi-objdump 
    ARGS -d ${CMAKE_BINARY_DIR}/${EXEC} -l > ${CMAKE_BINARY_DIR}/${EXEC}.s
    COMMENT "Generating disassembly"
)