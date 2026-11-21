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

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(_cc_link "${CMAKE_SOURCE_DIR}/compile_commands.json")
    set(_cc_real "${CMAKE_BINARY_DIR}/compile_commands.json")

    add_custom_target(compile_commands ALL
        COMMAND ${CMAKE_COMMAND} -E rm -f "${_cc_link}"
        COMMAND ${CMAKE_COMMAND} -E create_symlink "${_cc_real}" "${_cc_link}"
        COMMENT "Refreshing compile_commands.json symlink"
        VERBATIM
    )
endif()

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
