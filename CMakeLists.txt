cmake_minimum_required(VERSION 3.12)

# --- fetching FTXUI ---
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
    GIT_TAG v4.1.1
)
FetchContent_MakeAvailable(ftxui)
FetchContent_GetProperties(ftxui)
if (NOT ftxui_POPULATED)
    FetchContent_Populate(ftxui)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
# ----------------------

project(
    cpp-minesweeper
    VERSION 1.0.0
    DESCRIPTION "A C++ TUI Minesweeper game"
    LANGUAGES CXX
)

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tests)