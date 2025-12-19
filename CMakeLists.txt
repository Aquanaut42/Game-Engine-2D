cmake_minimum_required(VERSION 4.1)
project(Game_Engine_2D)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(
        Game_Engine_2D main.cpp
        world.cpp
        world.h
        window.cpp
        window.h
        asset_manager/asset_manager.cpp
        asset_manager/asset_manager.h
        UserInterface.cpp
        UserInterface.h
        fonts/font8.c
        fonts/font12.c
)

target_link_libraries(Game_Engine_2D ${SDL2_LIBRARIES})
