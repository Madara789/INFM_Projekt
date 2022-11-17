cmake_minimum_required (VERSION 3.8)

file(GLOB subscaleSRC
        "*.h" "*.cpp"
        "Subscale/*.h" "Subscale/*.cpp"
        "Subscale/CoreSetSeeker/*.h" "Subscale/CoreSetSeeker/*.cpp"
        "Subscale/DataLabeler/*.h" "Subscale/DataLabeler/*.cpp"
        "Subscale/DenseUnitGenerator/*.h" "Subscale/DenseUnitGenerator/*.cpp"
        "Subscale/Factory/*.h" "Subscale/Factory/*.cpp"
        "Subscale/Importer/*.h" "Subscale/Importer/*.cpp"
        "Subscale/Exporter/*.h" "Subscale/Exporter/*.cpp"
        "Subscale/SubspaceCombiner/*.h" "Subscale/SubspaceCombiner/*.cpp"
        "Subscale/SubspaceDetector/*.h" "Subscale/SubspaceDetector/*.cpp"
        "Helper/*.h" "Helper/*.cpp"
        )

add_executable(Core ${subscaleSRC})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Core PROPERTY CXX_STANDARD 20)
endif()
