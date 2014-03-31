
## source
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_Image_INCLUDE_DIRS})
include_directories(${INCLUDE_DIRS})
include_directories(${CONFIG_DIRS})

add_library(core ${FB_SOURCES})

add_executable(
	flappy_bear 
	${FB_MAIN}
	${FB_HEADERS}
	${FB_CONFIG}
	)

target_link_libraries(
	flappy_bear
	core	
	${SDL2_LIBRARIES}
	${SDL2_Image_LIBRARIES}
	)

## debug messages
message(STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})

