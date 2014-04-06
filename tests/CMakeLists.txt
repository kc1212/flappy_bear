
## unit tests
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_image_INCLUDE_DIRS})
include_directories(${SDL2_ttf_INCLUDE_DIRS})
include_directories(${INCLUDE_DIRS})
include_directories(${CONFIG_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

add_executable(
	ut_flappy_bear
	unit_tests.cpp
	${FB_HEADERS}
	) 

target_link_libraries(
	ut_flappy_bear 
	core
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} 
	${SDL2_LIBRARIES} 
	${SDL2_image_LIBRARIES}
	${SDL2_ttf_LIBRARIES}
	)

