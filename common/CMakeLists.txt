target_sources(${EXEC} PRIVATE src/nosys.c)

target_include_directories(${EXEC} PRIVATE include)
file(GLOB HEADERS include/*.h)
target_sources(${EXEC} PRIVATE ${HEADERS})