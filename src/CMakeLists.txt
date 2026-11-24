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

link_libraries(Includes)

add_library(model
	STATIC
		model/SyncGate.cpp
		model/VectorModel.cpp
		model/SyncingModel.cpp
)
target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(model PUBLIC Threads::Threads Exceptions)

add_subdirectory(args)
add_subdirectory(sorts)
add_subdirectory(visual)

add_executable(main
	main.cpp
	Registry.cpp

	app/Scene.cpp
	app/SortingManager.cpp
)

target_include_directories(main
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(main
	PRIVATE 
		SFML::Graphics 
		Args
		model
		Sorts
		Visual
)
