cmake_minimum_required(VERSION 3.12)
project("Advent_of_Code_2025" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(shared INTERFACE)
target_include_directories("shared" INTERFACE "./shared")

add_subdirectory("./01_secret_entrance")
