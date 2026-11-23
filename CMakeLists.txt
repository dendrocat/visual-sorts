cmake_minimum_required(VERSION 3.22)

#TODO: Add prebuilding SFML
#TODO: Add option for builing to one file without links
#TODO: Try to minimize count of build systems

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(VisualSorts LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_compile_options(
	-Wall -Wextra
    "$<$<CONFIG:Debug>:-O0;-g3>"
    "$<$<CONFIG:Release>:-O3;-DNDEBUG>"
)

option(BUILD_TESTS "Build tests" OFF)

add_subdirectory(src)

if (BUILD_TESTS)
	add_subdirectory(tests)
endif()
