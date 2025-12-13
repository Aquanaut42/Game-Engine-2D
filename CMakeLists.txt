cmake_minimum_required(VERSION 4.1)
project(Game_Engine_2D)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Game_Engine_2D main.cpp
        world.cpp
        world.h
        window.cpp
        window.h)

target_link_libraries(Game_Engine_2D ${SDL2_LIBRARIES})