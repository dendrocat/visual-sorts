find_package(Threads REQUIRED)

add_library(Model STATIC)

target_sources(Model
	PRIVATE
		SyncGate.cpp
		VectorModel.cpp
		SyncingModel.cpp

	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS include
		FILES
			include/model/SyncGate.hpp
			include/model/VectorModel.hpp
			include/model/SyncingModel.hpp
)

target_link_libraries(Model PUBLIC Threads::Threads Includes Exceptions)
