add_library(my_minesweeper
    board.cpp
    game.cpp
    ../include/my_minesweeper/board.hpp
    ../include/my_minesweeper/game.hpp
    ../include/my_minesweeper/constants.hpp
    
)
target_include_directories(my_minesweeper PUBLIC ../include)
target_link_libraries(my_minesweeper
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)
target_compile_features(my_minesweeper PUBLIC cxx_std_11)

