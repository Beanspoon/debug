target_include_directories(${EXEC} PRIVATE include)
file(GLOB HEADERS include/*.h)
target_sources(${EXEC} PRIVATE ${HEADERS}
    src/startup.c
    src/gpio_hal.c
    src/trace_hal.c
    src/core_systick_hal.c)