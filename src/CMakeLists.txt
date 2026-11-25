find_package(SFML 3 REQUIRED COMPONENTS Graphics)
find_package(Threads REQUIRED)

add_library(Includes INTERFACE)
target_include_directories(Includes
	INTERFACE
		${CMAKE_SOURCE_DIR}/src/include
)

add_library(Exceptions INTERFACE)
target_include_directories(Exceptions
	INTERFACE
		${CMAKE_SOURCE_DIR}/src/exceptions
)

add_subdirectory(args)
add_subdirectory(model)
add_subdirectory(sorts)
add_subdirectory(visual)
add_subdirectory(app)

add_executable(main
	main.cpp
	Registry.cpp
)

target_link_libraries(main
	PRIVATE
		SFML::Graphics
		Exceptions
		Args
		Model
		Sorts
		Visual
		App
)
