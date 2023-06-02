add_library(my_minesweeper
    board.cpp
    game.cpp
    uicomponents.cpp
    ../include/my_minesweeper/board.hpp
    ../include/my_minesweeper/game.hpp
    ../include/my_minesweeper/constants.hpp
    ../include/my_minesweeper/uicomponents.hpp
)
target_include_directories(my_minesweeper PUBLIC ../include)
target_link_libraries(my_minesweeper
    PUBLIC ftxui::screen
    PUBLIC ftxui::dom
    PUBLIC ftxui::component
)
target_compile_features(my_minesweeper PUBLIC cxx_std_11)

