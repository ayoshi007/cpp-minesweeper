#include <iostream>

#include <my_minesweeper/board.hpp>
#include <my_minesweeper/uicomponents.hpp>

/*
Driver class
Start game by using game.cpp
*/

int main() {
    GameUI::initializeContainer();
    GameUI::startGame();

    return 0;
}