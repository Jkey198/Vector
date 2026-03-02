cmake_minimum_required(VERSION 3.16)

# Project name and version
project(Vector VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Main executable
add_executable(test main.cpp)

# Include the current directory for headers
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Compiler warnings (per-target to avoid affecting GoogleTest)
if(MSVC)
    target_compile_options(test PRIVATE /W4)
else()
    target_compile_options(test PRIVATE -Wall -Werror -pedantic)
endif()

# Set output directory
set_target_properties(test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add tests subdirectory
add_subdirectory(tests)
