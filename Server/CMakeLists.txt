find_package(nlohmann_json CONFIG REQUIRED)
find_path(MLPACK_INCLUDE_DIRS "mlpack/mlpack.hpp")
find_package(Threads)

file(GLOB SOURCES
        "../SubscaleGPU/*.h" "../SubscaleGPU/*.cpp" "../SubscaleGPU/*.cuh" "../SubscaleGPU/*.cu"
        "../SubscaleGPU/BinomialCoeffCreator/*.cuh" "../SubscaleGPU/BinomialCoeffCreator/*.cu"
        "../SubscaleGPU/Clustering/*.h" "../SubscaleGPU/Clustering/*.cpp"
        "../SubscaleGPU/CoreSetCreator/*.h" "../SubscaleGPU/CoreSetCreator/*.cpp"
        "../SubscaleGPU/CsvDataHandler/*.h" "../SubscaleGPU/CsvDataHandler/*.cpp"
        "../SubscaleGPU/DenseUnitCreator/*.h" "../SubscaleGPU/DenseUnitCreator/*.cpp" "../SubscaleGPU/DenseUnitCreator/*.cuh" "../SubscaleGPU/DenseUnitCreator/*.cu"
        "../SubscaleGPU/DenseUnitMap/*.h" "../SubscaleGPU/DenseUnitMap/*.cpp" "../SubscaleGPU/DenseUnitMap/*.cuh" "../SubscaleGPU/DenseUnitMap/*.cu"
        "../SubscaleGPU/DoubleHashing/*.h" "../SubscaleGPU/DoubleHashing/*.cpp"
        "../SubscaleGPU/HelperFunctions/*.h" "../SubscaleGPU/HelperFunctions/*.cpp" "../SubscaleGPU/HelperFunctions/*.cuh" "../SubscaleGPU/HelperFunctions/*.cu"
        "../SubscaleGPU/LabelGenerator/*.h" "../SubscaleGPU/LabelGenerator/*.cpp"
        "../SubscaleGPU/MemoryManager/*.cuh" "../SubscaleGPU/MemoryManager/*.cu"
        "../SubscaleGPU/StadiumHashing/*.cuh" "../SubscaleGPU/StadiumHashing/*.cu"
        "../SubscaleGPU/Subscale/*.h" "../SubscaleGPU/Subscale/*.cpp"
        "../SubscaleGPU/SubscaleConfig/*.h" "../SubscaleGPU/SubscaleConfig/*.cpp"
        "../SubscaleGPU/SubspaceJoiner/*.h" "../SubscaleGPU/SubspaceJoiner/*.cpp" "../SubscaleGPU/SubspaceJoiner/*.cuh" "../SubscaleGPU/SubspaceJoiner/*.cu"
        "../SubscaleGPU/SubspaceMap/*.h" "../SubscaleGPU/SubspaceMap/*.cpp" "../SubscaleGPU/SubspaceMap/*.cuh" "../SubscaleGPU/SubspaceMap/*.cu"
        "../SubscaleGPU/Tables/*.h" "../SubscaleGPU/Tables/*.cpp" "../SubscaleGPU/Tables/*.cuh" "../SubscaleGPU/Tables/*.cu"
        "../SubscaleGPU/TimeMeasurement/*.h" "../SubscaleGPU/TimeMeasurement/*.cpp"
        "../SubscaleGPU/Remote/*.h" "../SubscaleGPU/Remote/*.cpp"
        )

add_executable(server ${SOURCES})

# compilation properties for CUDA
set_target_properties(server PROPERTIES CUDA_SEPARABLE_COMPILATION ON CUDA_ARCHITECTURES 70)
target_compile_options(server PRIVATE $<$<COMPILE_LANGUAGE:CUDA>: --relocatable-device-code=true>)

target_link_libraries(server PRIVATE myproto nlohmann_json nlohmann_json::nlohmann_json)