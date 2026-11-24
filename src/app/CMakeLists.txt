find_package(SFML 3 REQUIRED COMPONENTS Graphics)
find_package(Threads REQUIRED)

add_library(App STATIC)

target_sources(App
	PRIVATE
		Scene.cpp
		SortingManager.cpp
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS include
		FILES
			include/app/Scene.hpp
			include/app/SortingManager.hpp
)

target_link_libraries(App
	PRIVATE
		Threads::Threads
	PUBLIC
		SFML::Graphics
		Exceptions
		Model
		Sorts
		Visual
)

