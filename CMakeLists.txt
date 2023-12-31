cmake_minimum_required(VERSION 3.10)

project(layout)

add_subdirectory(raylib)
add_executable(test gui_test.cpp layout.cpp)

target_link_libraries(test raylib)

