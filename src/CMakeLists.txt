# library is made an object library for testing with doctest
set(my_minesweeper_sources
    core/constants.hpp
    core/constants.cpp
    core/starter.cpp
    core/starter.hpp
    game/board.cpp
    game/board.hpp
    game/controller.cpp
    game/controller.hpp
    ui/main_menu.cpp
    ui/main_menu.hpp
    ui/game_board.cpp
    ui/game_board.hpp
    ui/ui_helper.cpp
    ui/ui_helper.hpp
    ui/window.cpp
    ui/window.hpp
    doctest/doctest.h
)
add_library(my_minesweeper
    ${my_minesweeper_sources}
)
target_include_directories(my_minesweeper
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(my_minesweeper
    PUBLIC ftxui::screen
    PUBLIC ftxui::dom
    PUBLIC ftxui::component
)
target_compile_features(my_minesweeper PUBLIC cxx_std_11)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)
if (ENABLE_TESTING)
    add_compile_definitions(DOCTEST_CONFIG_DISABLE)
endif()