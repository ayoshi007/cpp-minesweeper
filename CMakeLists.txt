cmake_minimum_required(VERSION 3.12)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
# include(ExternalProject)

# --- fetching FTXUI ---
FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
    GIT_TAG v4.1.1
)
FetchContent_MakeAvailable(ftxui)
# ----------------------

option(ENABLE_TESTING "Build unit tests" ON)

project(
    cpp-minesweeper
    VERSION 1.0.0
    DESCRIPTION "A C++ TUI Minesweeper game"
    LANGUAGES CXX
)

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tests)