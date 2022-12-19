
set(SOURCES src/Main.cpp )

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Subscale/results)

add_executable(subscale ${SOURCES})
target_include_directories(subscale PRIVATE ../SubscaleGPU)
target_link_libraries(subscale PRIVATE subscale-lib)