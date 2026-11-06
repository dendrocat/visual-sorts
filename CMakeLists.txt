cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 3 REQUIRED COMPONENTS Graphics)

add_executable(main
    src/main.cpp
	src/registery.cpp
	src/Scene.cpp

	src/model/SyncGate.cpp
	src/model/VectorModel.cpp
	src/model/SyncingModel.cpp

    src/visual/VectorVisualizer.cpp
    src/visual/Bar.cpp

	src/sorts/SortingManager.cpp
)
target_compile_features(main PRIVATE cxx_std_23)
target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(main PRIVATE SFML::Graphics)
