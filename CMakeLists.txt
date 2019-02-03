cmake_minimum_required(VERSION 3.13)
project(minigame)
set(CMAKE_CXX_STANDARD 17)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

add_executable(minigame main.cpp Game.cpp Game.h LED.cpp LED.h)
target_link_libraries(minigame ${SDL2_LIBRARIES})