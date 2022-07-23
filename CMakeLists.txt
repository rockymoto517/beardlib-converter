cmake_minimum_required(VERSION 3.5)

project(BeardlibConverter VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(RapidJSON)
add_executable(Converter
    src/main.cpp)

ADD_LIBRARY(libs
    src/Converter.cpp)

target_link_libraries(libs ${RapidJSON})
target_link_libraries(Converter libs)