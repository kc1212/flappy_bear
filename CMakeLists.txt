cmake_minimum_required(VERSION 2.8)
project(flappy_bear)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_Image REQUIRED SDL2_image)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "-g -W -Wall -pedantic -framework Cocoa")
else()
    set(CMAKE_CXX_FLAGS "-g -W -Wall -pedantic")
endif()

add_subdirectory(src)

