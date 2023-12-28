cmake_minimum_required(VERSION 3.5)

project(BeardlibConverter VERSION 1.4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -pthread -std=c++20")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Keep this on if your lsp depends on it lol

set(SOURCES src/main.cpp 
            src/track.cpp
			src/xml.cpp
			src/files.cpp)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/json")
add_executable(Converter ${SOURCES})

target_link_libraries(Converter PRIVATE nlohmann_json::nlohmann_json)
