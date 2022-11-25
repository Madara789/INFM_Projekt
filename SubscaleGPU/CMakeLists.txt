cmake_minimum_required(VERSION 3.17)

# ATTENTION: nlohmann_json has to be installed with vcpkg before compilation
find_package(nlohmann_json CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_path(MLPACK_INCLUDE_DIRS "mlpack/mlpack.hpp")

file(GLOB subscaleSRC
        "src/Main.cpp"
        "*.h" "*.cpp" "*.cuh" "*.cu"
        "BinomialCoeffCreator/*.cuh" "BinomialCoeffCreator/*.cu"
        "Client/*.h" "Client/*.cpp"
        "Clustering/*.h" "Clustering/*.cpp"
        "CoreSetCreator/*.h" "CoreSetCreator/*.cpp"
        "CsvDataHandler/*.h" "CsvDataHandler/*.cpp"
        "DenseUnitCreator/*.h" "DenseUnitCreator/*.cpp" "DenseUnitCreator/*.cuh" "DenseUnitCreator/*.cu"
        "DenseUnitMap/*.h" "DenseUnitMap/*.cpp" "DenseUnitMap/*.cuh" "DenseUnitMap/*.cu"
        "DoubleHashing/*.h" "DoubleHashing/*.cpp"
        "HelperFunctions/*.h" "HelperFunctions/*.cpp" "HelperFunctions/*.cuh" "HelperFunctions/*.cu"
        "LabelGenerator/*.h" "LabelGenerator/*.cpp"
        "MemoryManager/*.cuh" "MemoryManager/*.cu"
        "StadiumHashing/*.cuh" "StadiumHashing/*.cu"
        "Subscale/*.h" "Subscale/*.cpp"
        "SubscaleConfig/*.h" "SubscaleConfig/*.cpp"
        "SubspaceJoiner/*.h" "SubspaceJoiner/*.cpp" "SubspaceJoiner/*.cuh" "SubspaceJoiner/*.cu"
        "SubspaceMap/*.h" "SubspaceMap/*.cpp" "SubspaceMap/*.cuh" "SubspaceMap/*.cu"
        "Tables/*.h" "Tables/*.cpp" "Tables/*.cuh" "Tables/*.cu"
        "TimeMeasurement/*.h" "TimeMeasurement/*.cpp"
        "Remote/*.h" "Remote/*.cpp"
        )

add_executable(subscale ${subscaleSRC})

# compilation properties for CUDA
set_target_properties(subscale PROPERTIES CUDA_SEPARABLE_COMPILATION ON CUDA_ARCHITECTURES 70)
target_compile_options(subscale PRIVATE $<$<COMPILE_LANGUAGE:CUDA>: --relocatable-device-code=true>)

# link libraries (ATTENTION: change the path of mlpack to compile the code)
target_link_libraries(subscale PUBLIC nlohmann_json nlohmann_json::nlohmann_json gRPC::grpc++)