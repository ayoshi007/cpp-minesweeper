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
        GameLogic::Board::Cover cover;
        ftxui::Component renderer;
    };
    
    class GameBoard {
        private:
        int width {};
        int height {};
        int mx {};
        int my {};
        int selected_row {};
        int selected_col {};
        int mine_count {};
        int canvas_dimension {};
        GameLogic::BoardController board_controller;
        std::vector<std::vector<BoardCell>> game_board;
        ftxui::Component container;
        ftxui::Component renderer;

        void initialize_cells();
        void initialize_renderer();
        public:
        static ftxui::Color border_color;
        static ftxui::Color fill_color;
        static ftxui::Color flag_color;
        static ftxui::Color mine_color_win;
        static ftxui::Color mine_color_detonated;

        GameBoard(int width, int height, int mine_count);
        ftxui::Component get_game_board_renderer();
    };
    class GameSideBar {
        private:

        public:
        static GameUI::GameBoard build_side_bar(std::function<void()> return_to_menu_action);
    };

}

#endif // GAME_BOARD_HPP
