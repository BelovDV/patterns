cmake_minimum_required(VERSION 3.19)

project(test)

add_executable(test1 main.cpp)

set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/sfml/lib/cmake/SFML")
find_package(SFML 2.5 REQUIRED graphics window system)
target_link_libraries(test1 sfml-graphics)