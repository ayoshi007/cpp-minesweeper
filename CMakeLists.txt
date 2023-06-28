cmake_minimum_required(VERSION 3.20)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

# --- fetching FTXUI ---
FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
    GIT_TAG v4.1.1
)
FetchContent_MakeAvailable(ftxui)
# ----------------------
# --- fetching doctest ---
FetchContent_Declare(doctest
    GIT_REPOSITORY https://github.com/doctest/doctest
    GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)
# ------------------------

option(CPPMS_ENABLE_TESTING "Build unit tests" ON)
option(CPPMS_RUN_UI_TESTS "Build interactive UI tests" OFF)

# set(FTXUI_BUILD_EXAMPLES OFF)
# set(FTXUI_BUILD_TESTS OFF)


if (NOT CPPMS_ENABLE_TESTING)
    add_definitions("-DDOCTEST_CONFIG_DISABLE")
endif()

project(
    cpp-minesweeper
    VERSION 1.0.0
    DESCRIPTION "A C++ TUI Minesweeper game"
    LANGUAGES CXX
)

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tests)