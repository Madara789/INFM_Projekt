cmake_minimum_required(VERSION 3.16)

set(CMAKE_TOOLCHAIN_FILE include/vcpkg/scripts/buildsystems/vcpkg.cmake)

set(GCC_COVERAGE_COMPILE_FLAGS "-fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem /usr/local/cuda/include ${GCC_COVERAGE_COMPILE_FLAGS}")
set(VCPKG_TARGET_TRIPLET x64-linux)

include(include/vcpkg/scripts/buildsystems/vcpkg.cmake)

FILE(COPY SubscaleGPU/Config/config.json DESTINATION SubscaleGPU/Config)

project("SubscaleGPU")
enable_language(CUDA)
add_subdirectory("Proto")
add_subdirectory("Client")
add_subdirectory("Server")
add_subdirectory("Subscale")
add_subdirectory("SubscaleGPU")