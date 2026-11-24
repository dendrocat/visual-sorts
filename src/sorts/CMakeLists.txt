add_library(Sorts INTERFACE)

target_include_directories(Sorts
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Sorts INTERFACE Model)
