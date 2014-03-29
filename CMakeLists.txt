cmake_minimum_required(VERSION 2.8)
project(flappy_bear)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries
# http://stackoverflow.com/questions/6921695/how-can-i-build-a-c-project-with-multiple-interdependent-subdirectories
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_Image REQUIRED SDL2_image)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "-g -W -Wall -pedantic -framework Cocoa")
else()
    set(CMAKE_CXX_FLAGS "-g -W -Wall -pedantic")
endif()

file(GLOB_RECURSE FB_CPP "src/*.cpp")
file(GLOB_RECURSE FB_HPP "include/*.hpp")
file(GLOB_RECURSE FB_CONFIG "config/*.hpp")

set(INCLUDE_DIRS "")

foreach(_headerFile ${FB_HPP})
	get_filename_component(_dir ${_headerFile} PATH)
	list (APPEND INCLUDE_DIRS ${_dir})
endforeach()

foreach(_configFile ${FB_CONFIG})
	get_filename_component(_dir ${_configFile} PATH)
	list (APPEND INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_Image_INCLUDE_DIRS})
include_directories(${INCLUDE_DIRS})

add_executable(flappy_bear ${FB_CPP})

target_link_libraries(flappy_bear ${SDL2_LIBRARIES} ${SDL2_Image_LIBRARIES})
