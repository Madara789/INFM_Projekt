cmake_minimum_required (VERSION 3.8)

project ("Subscale")

add_subdirectory ("Core")

FILE(COPY data/ DESTINATION Core/Debug/data)