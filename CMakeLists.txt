cmake_minimum_required(VERSION 3.15)
project(tetris)

set(CMAKE_CXX_STANDARD 14)

add_executable(1 main.cpp block_def.h block_realization.cpp)
add_executable(2 trial_timer.cpp)
add_executable(3 trial_key_event.cpp)

find_package(Threads REQUIRED)
find_package(Curses REQUIRED)
target_link_libraries(2 Threads::Threads)
target_link_libraries(3 ncurses)
target_link_libraries(1 ncurses)