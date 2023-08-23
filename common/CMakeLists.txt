target_sources(${EXEC} PRIVATE src/nosys.c)

target_include_directories(${EXEC} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
file(GLOB HEADERS ${CMAKE_CURRENT_LIST_DIR}/include/*.h)
target_sources(${EXEC} PRIVATE ${HEADERS})