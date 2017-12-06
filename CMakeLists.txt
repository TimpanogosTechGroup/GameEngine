cmake_minimum_required(VERSION 3.8)
project(GameEngine)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES GameEngine/main.cpp)
add_executable(GameEngine ${SOURCE_FILES} GameEngine/main.cpp)