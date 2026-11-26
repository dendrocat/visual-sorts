add_library(Sorts STATIC)

target_sources(Sorts
	PRIVATE
		AlgorithmFactory.cpp
	
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS include
		FILES
			include/sorts/SortingAlgorithm.hpp
			include/sorts/AlgorithmFactory.hpp
)

target_link_libraries(Sorts PUBLIC Model)
