cmake_minimum_required (VERSION 3.8)

file(GLOB subscaleSRC
        "*.h" "*.cpp"
        "Data/*.h" "Data/*.cpp"
        "Exporter/*.h" "Exporter/*.cpp"
        "Importer/*.h" "Importer/*.cpp"
        "Subscale/*.h" "Subscale/*.cpp"
        "Subscale/CoreSetGenerator/*.h" "Subscale/CoreSetGenerator/*.cpp"
        "Subscale/DataLabeler/*.h" "Subscale/DataLabeler/*.cpp"
        "Subscale/DenseUnitGenerator/*.h" "Subscale/DenseUnitGenerator/*.cpp"
        "Subscale/Factory/*.h" "Subscale/Factory/*.cpp"
        )

add_executable(Core ${subscaleSRC})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Core PROPERTY CXX_STANDARD 20)
endif()
