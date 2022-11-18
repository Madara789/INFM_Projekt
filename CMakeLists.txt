cmake_minimum_required (VERSION 3.8)

project ("Subscale")

add_subdirectory("include")
add_subdirectory ("Core")

FILE(COPY data/ DESTINATION Core/Debug/data)
FILE(COPY config.json DESTINATION Core/Debug)