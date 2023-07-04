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
)
add_library(my_minesweeper_obj OBJECT
    ${my_minesweeper_sources}
)
target_include_directories(my_minesweeper_obj
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(my_minesweeper_obj
    PUBLIC ftxui::screen
    PUBLIC ftxui::dom
    PUBLIC ftxui::component
    PUBLIC doctest::doctest
)
target_compile_features(my_minesweeper_obj PUBLIC cxx_std_17)
target_compile_options(my_minesweeper_obj PUBLIC -Wall -Wextra -Wpedantic -Werror)
if (CPPMS_RUN_UI_TESTS)
    add_compile_definitions(RUN_UI_TESTS)
endif()