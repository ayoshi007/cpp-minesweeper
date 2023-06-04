add_library(my_minesweeper
    core/constants.hpp
    core/controller.cpp
    core/controller.hpp
    core/starter.cpp
    core/starter.hpp
    game/board.cpp
    game/board.hpp
    game/session.cpp
    game/session.hpp
    ui/main_menu.cpp
    ui/main_menu.hpp
    ui/game_board.cpp
    ui/game_board.hpp
    ui/window.cpp
    ui/window.hpp
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

