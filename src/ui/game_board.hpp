#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <ftxui/component/component.hpp>
#include <game/controller.hpp>

// define all components and elements of the game board here

namespace GameUI {
    class GameBoard {
        GameLogic::BoardController board_controller;
    };
}

#endif // GAME_BOARD_HPP
