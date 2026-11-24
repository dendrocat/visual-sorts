add_library(Args STATIC)

target_sources(Args
	PRIVATE
		Usage.cpp
		ArgsParser.cpp
		ArgsValidator.cpp
		Args.cpp

	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS include/args
		FILES
			include/args/Usage.hpp
			include/args/Args.hpp
)

target_include_directories(Args
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Args PRIVATE Exceptions)
