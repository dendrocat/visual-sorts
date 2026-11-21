find_package(SFML 3 REQUIRED COMPONENTS Graphics)
find_package(Threads REQUIRED)

add_library(model STATIC
    model/SyncGate.cpp
    model/VectorModel.cpp
    model/SyncingModel.cpp
)
target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(model PUBLIC Threads::Threads)

add_executable(main
    main.cpp
	Registry.cpp

	args/ArgsParser.cpp
	args/ArgsValidator.cpp
	args/Args.cpp

    visual/VectorVisualizer.cpp
    visual/Bar.cpp
	visual/Ellipse.cpp
	visual/Scene.cpp

	sorts/SortingManager.cpp
)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(main PRIVATE model SFML::Graphics)
