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

#include <memory>

// define all components and elements of the game board here

namespace GameUI {
    enum CellSymbol {
        Empty,
        Number,
        Flag,
        BadFlag,
        Mine,
        Detonated
    };
    struct BoardCell {
        int row;
        int col;
        bool hovered;
        GameUI::CellSymbol symbol;
        ftxui::Component renderer;
    };
    
    class GameBoard {
        private:
        int width {};
        int height {};
        int mine_count {};
        int mx {};
        int my {};
        int selected_row {};
        int selected_col {};
        bool game_is_done {};
        int canvas_dimension {};

        GameLogic::BoardController board_controller;
        std::vector<std::vector<BoardCell>> game_board;
        ftxui::Component renderer;

        static ftxui::Color bg_color;
        static ftxui::Color bad_bg_color;
        static ftxui::Color border_color;
        static ftxui::Color bad_border_color;

        static ftxui::Color number_color;
        static ftxui::Color flag_color;
        static ftxui::Color bad_flag_color;
        static ftxui::Color mine_color;
        static ftxui::Color mine_color_detonated;

        static std::function<void(ftxui::Canvas&, int, ftxui::Color)> fill_cell;
        static std::function<void(ftxui::Canvas&, int, ftxui::Color, ftxui::Color)> draw_border;
        static std::function<void(ftxui::Canvas&, int, ftxui::Color, ftxui::Color)> draw_flag;
        static std::function<void(ftxui::Canvas&, int, ftxui::Color, ftxui::Color)> draw_mine;
        static std::function<void(ftxui::Canvas&, int, ftxui::Color, ftxui::Color, int)> draw_number;

        void initialize_cells();
        void initialize_renderer();

        public:
        GameBoard();
        GameBoard(int width, int height, int mine_count, int dimension);
        GameBoard(int width, int height, int mine_count, int dimension, int seed);

        int get_mx();
        int get_my();
        int get_selected_row();
        int get_selected_col();
        ftxui::Element get_flag_label();
        ftxui::Component get_new_game_button();

        void set_canvas_dimension(int new_dimension);
        ftxui::Component get_game_board_renderer();
    };
}

#endif // GAME_BOARD_HPP
