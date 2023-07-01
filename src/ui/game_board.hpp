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
        int mx;
        int my;
        GameLogic::BoardController board_controller;
        std::vector<std::vector<BoardCell>> game_board;

        public:
        GameBoard(int width, int height, int mine_count);
    };
    class GameSideBar {
        private:

        public:
        static GameUI::GameBoard build_side_bar(std::function<void()> return_to_menu_action);
    };
    
}

#endif // GAME_BOARD_HPP
