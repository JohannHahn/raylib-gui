cmake_minimum_required(VERSION 3.10)

project(gui)

add_subdirectory(raylib)
add_executable(test gui_test.cpp layout.cpp gui.cpp)

target_link_libraries(test PUBLIC raylib)

