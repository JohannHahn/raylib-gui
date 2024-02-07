cmake_minimum_required(VERSION 3.12)

project(layout)

add_subdirectory(raylib)

add_executable(test gui_test.cpp)
target_link_libraries(test raylib)

