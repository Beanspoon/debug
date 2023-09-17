target_include_directories(${EXEC} PRIVATE include)
file(GLOB HEADERS include/*.h)
target_sources(${EXEC} PRIVATE ${HEADERS}
    src/nosys.c
    src/utils.c
    src/maths_utils.c)