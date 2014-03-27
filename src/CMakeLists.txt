include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_Image_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(player player.cpp)
add_executable(flappy_bear main.cpp)

target_link_libraries(flappy_bear ${SDL2_LIBRARIES} ${SDL2_Image_LIBRARIES} player)


