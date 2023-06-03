#include <iostream>

#include <my_minesweeper/board.hpp>
#include <my_minesweeper/ui/main_menu.hpp>
#include <my_minesweeper/ui/ui_control.hpp>

/*
Driver class
Start game by using game.cpp
*/

int main() {
    GameUI::initializeContainer();
    GameUI::startGame();

    return 0;
}