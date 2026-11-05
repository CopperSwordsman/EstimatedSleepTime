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
        compile.h
        handling.cpp
        compile.cpp
        maps.cpp
        maps.h
        infonode.cpp
        infonode.h
        Heap.cpp
        Heap.h

)
target_link_libraries(EstimatedSleep PRIVATE SFML::Graphics)

# Copy assets and dataset next to the executable after every build
add_custom_command(TARGET EstimatedSleep POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:EstimatedSleep>/assets
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/sleep_health_dataset.csv
        $<TARGET_FILE_DIR:EstimatedSleep>/sleep_health_dataset.csv)