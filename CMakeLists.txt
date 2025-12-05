cmake_minimum_required(VERSION 3.12)
project("Advent_of_Code_2025" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(shared INTERFACE)
target_include_directories(shared INTERFACE "./shared")

add_subdirectory("./01_secret_entrance")
add_subdirectory("./02_gift_shop")
add_subdirectory("./03_lobby")
add_subdirectory("./04_printing_department")
add_subdirectory("./05_cafeteria")
