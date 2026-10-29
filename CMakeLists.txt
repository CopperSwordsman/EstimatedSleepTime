cmake_minimum_required(VERSION 4.1)
project(EstimatedSleepTime)

set(CMAKE_CXX_STANDARD 20)

add_executable(EstimatedSleepTime main.cpp
        handling.cpp
        compile.cpp
        maps.cpp
        maps.h
        infonode.cpp
        infonode.h
        Heap.cpp
        Heap.h
)
configure_file(${CMAKE_SOURCE_DIR}/sleep_health_dataset.csv ${CMAKE_BINARY_DIR}/sleep_health_dataset.csv COPYONLY)