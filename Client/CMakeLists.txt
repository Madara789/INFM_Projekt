find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(Threads)
find_package(nlohmann_json CONFIG REQUIRED)

set(SOURCES src/Main.cpp 
            src/Config.h src/Config.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(client ${SOURCES})
target_include_directories(client PRIVATE ../SubscaleGPU ../Proto)
target_link_libraries(client PRIVATE myproto subscale-lib gRPC::grpc++ nlohmann_json nlohmann_json::nlohmann_json)

FILE(COPY config.json DESTINATION ${CMAKE_BINARY_DIR}/Client)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/config.override.json)
    message("Override Config Exists")
    FILE(COPY config.override.json DESTINATION ${CMAKE_BINARY_DIR}/Client)
endif()
