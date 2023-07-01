#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <game/controller.hpp>

#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/canvas.hpp>

// define all components and elements of the game board here

namespace GameUI {
    struct BoardCell {
        int row;
        int col;
        ftxui::Color border_color;
        ftxui::Color fill_color;
        ftxui::Component renderer;
    };
    class GameBoard {
        private:
        GameLogic::BoardController board_controller;
        std::vector<std::vector<BoardCell>> game_board;
        static ftxui::Component container;
        
        public:
        static ftxui::Component build_container();
        static GameUI::GameBoard build_game_board_ui(int width, int height, int mine_count);

    };
}

#endif // GAME_BOARD_HPP
