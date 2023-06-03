add_library(my_minesweeper
    ui/main_menu.cpp
    ui/ui_control.cpp
    ../include/my_minesweeper/constants.hpp
    ../include/my_minesweeper/ui/main_menu.hpp
    ../include/my_minesweeper/ui/ui_control.hpp
)
target_include_directories(my_minesweeper PUBLIC ../include)
target_link_libraries(my_minesweeper
    PUBLIC ftxui::screen
    PUBLIC ftxui::dom
    PUBLIC ftxui::component
)
target_compile_features(my_minesweeper PUBLIC cxx_std_11)

