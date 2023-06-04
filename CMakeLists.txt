cmake_minimum_required(VERSION 3.12)
project(
    cpp-minesweeper
    VERSION 1.0.0
    DESCRIPTION "A C++ TUI Minesweeper game"
    LANGUAGES CXX
)

find_package(ftxui)

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tests)