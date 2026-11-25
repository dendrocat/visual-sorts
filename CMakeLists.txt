cmake_minimum_required(VERSION 3.22)

#TODO: Add prebuilding SFML
#TODO: Add option for builing to one file without links

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(VisualSorts LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_compile_options(-Wall -Wextra -Wpedantic -pedantic-errors -Werror)

option(BUILD_TESTS "Build tests" OFF)

add_subdirectory(src)

if (BUILD_TESTS)
	add_subdirectory(tests)
endif()

if (CMAKE_EXPORT_COMPILE_COMMANDS)
	file(CREATE_LINK
		"${CMAKE_BINARY_DIR}/compile_commands.json"
		"${CMAKE_SOURCE_DIR}/build/compile_commands.json"
		SYMBOLIC
	)
endif()
