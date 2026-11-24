find_package(SFML 3 REQUIRED COMPONENTS Graphics)
find_package(Threads REQUIRED)

add_library(App STATIC)

target_sources(App
	PRIVATE
		Scene.cpp
		SortingManager.cpp
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS include/app
		FILES
			include/app/Scene.hpp
			include/app/SortingManager.hpp
)

target_include_directories(App
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(App
	PRIVATE
		SFML::Graphics
		Threads::Threads
		Exceptions
		Sorts
		Visual
)

