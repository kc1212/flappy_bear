include_directories(${SDL2_INCLUDE_DIRS})

add_executable(flappy_bear main.cpp)

target_link_libraries(flappy_bear ${SDL2_LIBRARIES})

