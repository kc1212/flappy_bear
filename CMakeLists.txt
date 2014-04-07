cmake_minimum_required(VERSION 2.8)
project(flappy_bear_project)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries
# http://stackoverflow.com/questions/6921695/how-can-i-build-a-c-project-with-multiple-interdependent-subdirectories
# SDL2 libraries
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_image REQUIRED SDL2_image)
pkg_search_module(SDL2_ttf REQUIRED SDL2_ttf)

## boost settings and libraries
## add components when required
set(Boost_USE_STATIC_LIBS       ON)
set(Boost_USE_MULTITHREADED     OFF)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

## set compiler flags
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(PLATFORM_FLAGS "")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(PLATFORM_FLAGS "")
else()
	set(PLATFORM_FLAGS "")
endif()
set(CMAKE_CXX_FLAGS "${PLATFORM_FLAGS} -W -Wall -pedantic -Werror -Wextra -std=c++98 -Wno-variadic-macros")
set(CMAKE_CXX_FLAGS_RELEASE "${PLATFORM_FLAGS} -O2")
set(CMAKE_CXX_FLAGS_DEBUG "${PLATFORM_FLAGS} -O0 -g")

 # set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Debug' as none was specified.")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
  # set the possible values of build type for cmake-gui
  # set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

## set include and config directories
## TODO bad to use GLOB_RESURSE apparently
file(GLOB_RECURSE FB_HEADERS "include/*.hpp")
file(GLOB_RECURSE FB_CONFIG "config/*.hpp")

set(INCLUDE_DIRS "")
set(CONFIG_DIRS "")

foreach(_headerFile ${FB_HEADERS})
	get_filename_component(_dir ${_headerFile} PATH)
	list (APPEND INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

foreach(_configFile ${FB_CONFIG})
	get_filename_component(_dir ${_configFile} PATH)
	list (APPEND CONFIG_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES CONFIG_DIRS)

# file(GLOB_RECURSE FB_SOURCES "*.cpp")
## set all the source files
set(FB_SOURCES 
	"${PROJECT_SOURCE_DIR}/src/texture.cpp"
	"${PROJECT_SOURCE_DIR}/src/player.cpp" 
	"${PROJECT_SOURCE_DIR}/src/background.cpp" 
	"${PROJECT_SOURCE_DIR}/src/utils.cpp"
	"${PROJECT_SOURCE_DIR}/src/obstacle.cpp"
	"${PROJECT_SOURCE_DIR}/src/world.cpp"
	"${PROJECT_SOURCE_DIR}/src/game_entity.cpp"
	"${PROJECT_SOURCE_DIR}/src/text_view.cpp"
	)
set(FB_MAIN "${PROJECT_SOURCE_DIR}/src/main.cpp")


## debug messages
message(STATUS "FB_HEAERS: " ${FB_HEADERS})
message(STATUS "FB_CONFIG: " ${FB_CONFIG})
message(STATUS "FB_SOURCES: " ${FB_SOURCES})
message(STATUS "FB_MAIN: " ${FB_MAIN})
message(STATUS "SDL2_INCLUDE_DIRS: " ${SDL2_INCLUDE_DIRS})
message(STATUS "SDL2_image_INCLUDE_DIRS: " ${SDL2_image_INCLUDE_DIRS})
message(STATUS "SDL2_ttf_INCLUDE_DIRS: " ${SDL2_ttf_INCLUDE_DIRS})
message(STATUS "INCLUDE_DIRS: " ${INCLUDE_DIRS})
message(STATUS "CONFIG_DIRS: " ${CONFIG_DIRS})
message(STATUS "SDL2_LIBRARIES: "${SDL2_LIBRARIES})
message(STATUS "SDL2_image_LIBRARIES: " ${SDL2_image_LIBRARIES})
message(STATUS "SDL2_ttf_LIBRARIES: " ${SDL2_ttf_LIBRARIES})

## adding sub directories
add_subdirectory(src)
add_subdirectory(tests)

