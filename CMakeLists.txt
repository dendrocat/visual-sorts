cmake_minimum_required(VERSION 3.22)

#TODO: Add prebuilding SFML
#TODO: Add option for builing to one file without links
#TODO: Try to minimize count of build systems

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 3 REQUIRED COMPONENTS Graphics)
find_package(Threads REQUIRED)

add_compile_options(-Wall -Wextra -Wpedantic -pedantic-errors -Werror)

add_library(model OBJECT
    src/model/SyncGate.cpp
    src/model/VectorModel.cpp
    src/model/SyncingModel.cpp
)
target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(main
    src/main.cpp
	src/registery.cpp
	src/Scene.cpp

    $<TARGET_OBJECTS:model>

    src/visual/VectorVisualizer.cpp
    src/visual/Bar.cpp
	src/visual/Ellipse.cpp

	src/sorts/SortingManager.cpp
)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(main PRIVATE SFML::Graphics)

add_executable(test src/test.cpp $<TARGET_OBJECTS:model>)
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(test PRIVATE Threads::Threads)
