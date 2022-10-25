cmake_minimum_required (VERSION 3.8)

project ("Subscale")

add_subdirectory ("Core")

install(DIRECTORY data/ DESTINATION data)