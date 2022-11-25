find_package(Threads)

set(SOURCES src/Main.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(client ${SOURCES})
target_include_directories(client PRIVATE ../Proto/generated)
target_link_libraries(client PRIVATE myproto)