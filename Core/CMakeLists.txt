# CMakeList.txt: CMake-Projekt für "Core". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (Core "Core.cpp" "Core.h" "Subscale.h" "Data/Cluster.h"  "Subscale.cpp" "Data/DataSet.h"  "Subscale/DataLabelerInterface.h" "Subscale/DataLabeler/SequentialDataLabeler.h" "Subscale/Factory/SequentialSubscaleFactory.h" "Subscale/SubscaleFactoryInterface.h" "Subscale/Factory/SequentialSubscaleFactory.cpp" "Subscale/DataLabeler/SequentialDataLabeler.cpp" "Data/Dimension.h" "Data/Dimension.cpp" "Data/DataSet.cpp" "Subscale/CoreSetGeneratorInterface.h" "Subscale/DenseUnitGeneratorInterface.h" "Subscale/DenseUnitGenerator/SequentialDenseUnitGenerator.h" "Subscale/CoreSetGenerator/SequentialCoreSetGenerator.h" "Data/CoreSet.h" "Data/DenseUnit.h" "ImporterInterface.h" "Importer/CsvImporter.h" "Importer/CsvImporter.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Core PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
