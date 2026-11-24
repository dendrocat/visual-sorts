find_package(SFML 3 REQUIRED COMPONENTS Graphics)

add_library(Visual STATIC)

target_sources(Visual
	PRIVATE
		VectorVisualizer.cpp
		Bar.cpp
		Ellipse.cpp

	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS include/visual
		FILES
			include/visual/VectorVisualizer.hpp
			include/visual/Statistics.hpp
			include/visual/VisualizerFactory.hpp
)

target_include_directories(Visual
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Visual
	PUBLIC
		SFML::Graphics
		Exceptions
		Model
)
