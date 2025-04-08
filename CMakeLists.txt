cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(GallowsGame LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(GallowsGame src/main.cpp)
