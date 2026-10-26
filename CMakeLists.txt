cmake_minimum_required(VERSION 3.24)
project(EstimatedSleep LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(EstimatedSleep
        main.cpp
        Load_window.cpp
        compile.cpp
        handling.cpp)
target_link_libraries(EstimatedSleep PRIVATE SFML::Graphics)

configure_file(${CMAKE_SOURCE_DIR}/sleep_health_dataset.csv
        ${CMAKE_BINARY_DIR}/sleep_health_dataset.csv COPYONLY)