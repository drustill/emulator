cmake_minimum_required(VERSION 3.10)

project(emulator VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(sdl)
