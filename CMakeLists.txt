cmake_minimum_required(VERSION 3.5)

project(BeardlibConverter VERSION 1.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -pthread -std=c++20")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(SOURCES src/main.cpp 
            src/Converter.cpp 
            src/Converter.h)

include_directories("${CMAKE_BINARY_DIR}/Include")
add_executable(Converter ${SOURCES})

target_precompile_headers(Converter PRIVATE src/headers.h)

target_compile_definitions(Converter PUBLIC RESOURCE_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/")