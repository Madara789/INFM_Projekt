find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(Threads)

set(SOURCES src/Main.cpp
            src/SubscaleRoutesImpl.h src/SubscaleRoutesImpl.cpp            
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(server ${SOURCES})
target_include_directories(server PRIVATE ../SubscaleGPU ../Proto)
target_link_libraries(server PRIVATE myproto subscale-lib gRPC::grpc++)