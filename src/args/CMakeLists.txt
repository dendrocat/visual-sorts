add_library(Args STATIC)

target_sources(Args
	PRIVATE
		Usage.cpp
		ArgsParser.cpp
		ArgsValidator.cpp
		Args.cpp

	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS include
		FILES
			include/args/Usage.hpp
			include/args/Args.hpp
)

target_link_libraries(Args PUBLIC Includes)
