add_library(Visual STATIC)

target_sources(Visual
	PRIVATE
		VectorVisualizer.cpp
		Bar.cpp
		Ellipse.cpp
		VisualizerFactory.cpp

	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS include
		FILES
			include/visual/VectorVisualizer.hpp
			include/visual/Statistics.hpp
			include/visual/VisualizerFactory.hpp
)

target_link_libraries(Visual
	PUBLIC
		SFML::Graphics
		Includes
		Exceptions
		Model
)
