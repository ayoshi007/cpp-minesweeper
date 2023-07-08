#include <ui/game_board.hpp>
#include <ui/ui_helper.hpp>

#include <doctest/doctest.h>

#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/requirement.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/canvas.hpp>

#include <functional>
#include <vector>
#include <tuple>

using namespace ftxui;

namespace GameUI {
    Color GameBoard::border_color = Color::GrayDark;
    Color GameBoard::fill_color = Color::DarkBlue;
    Color GameBoard::flag_color = Color::Cyan;
    Color GameBoard::mine_color_detonated = Color::Salmon1;
    Color GameBoard::mine_color_win = Color::Gold1;

    std::function<void(ftxui::Canvas&, int, ftxui::Color)> GameBoard::draw_border = [] (Canvas& canvas, int dimension, Color color) {
        canvas.DrawPointLine(0, 0, dimension - 1, 0, color);
        canvas.DrawPointLine(dimension - 1, 0, dimension - 1, dimension - 1, color);
        canvas.DrawPointLine(0, 0, 0, dimension - 1, color);
        canvas.DrawPointLine(0, dimension - 1, dimension - 1, dimension - 1, color);
    };
    
    std::function<void(ftxui::Canvas&, int, ftxui::Color)> GameBoard::draw_flag = [] (Canvas& canvas, int dimension, Color color) {
        canvas.DrawText(dimension / 2, dimension / 2, "^", [=] (Pixel& p) {
            p.background_color = color;
            p.foreground_color = Color::Black;
        });
    };
    std::function<void(ftxui::Canvas&, int, ftxui::Color)> GameBoard::draw_mine = [] (Canvas& canvas, int dimension, Color color) {
        canvas.DrawText(dimension / 2, dimension / 2, "*", [=] (Pixel& p) {
            p.background_color = color;
            p.foreground_color = Color::Black;
        });
    };
    std::function<void(ftxui::Canvas&, int, ftxui::Color, int)> GameBoard::draw_number = [] (Canvas& canvas, int dimension, Color color, int number) {
        canvas.DrawText(dimension / 2, dimension / 2, std::to_string(number), [=] (Pixel& p) {
            p.background_color = Color::Black;
            p.foreground_color = color;
        });
    };
    
    GameBoard::GameBoard(int w, int h, int mines) : 
        width {w},
        height {h},
        mine_count {mines},
        mx {},
        my {},
        selected_row {},
        selected_col {},
        game_is_done {false},
        board_controller {}
        {
        board_controller.initialize_board(w, h, mines);
        canvas_dimension = 12;
        initialize_cells();
        initialize_renderer();
    }
    GameBoard::GameBoard(int w, int h, int mines, int seed) :
        width {w},
        height {h},
        mine_count {mines},
        mx {},
        my {},
        selected_row {},
        selected_col {},
        game_is_done {false},
        board_controller {}
        {
        board_controller.initialize_board(w, h, mines, seed);
        canvas_dimension = 12;
        initialize_cells();
        initialize_renderer();
    }
    
    void GameBoard::initialize_cells() {
        game_board = std::vector<std::vector<BoardCell>> (height);
        for (int cell_row = 0; cell_row < height; cell_row++) {
            game_board[cell_row] = std::vector<BoardCell> (width);
            for (int cell_col = 0; cell_col < width; cell_col++) {
                game_board[cell_row][cell_col] = {
                    cell_row, cell_col,
                    false,
                    GameLogic::Board::Cover::Covered,
                    Renderer([cell_row, cell_col, this] {
                        Canvas cell_canvas = Canvas(canvas_dimension, canvas_dimension);
                        draw_border(cell_canvas, canvas_dimension, GameBoard::border_color);    
                        if (game_board[cell_row][cell_col].cover == GameLogic::Board::Cover::Mine) {
                            Color mine_color = board_controller.is_game_won() ? GameBoard::mine_color_win : GameBoard::mine_color_detonated;
                            draw_mine(cell_canvas, canvas_dimension, mine_color);
                        } else if (game_board[cell_row][cell_col].cover == GameLogic::Board::Cover::Flagged) {
                            draw_flag(cell_canvas, canvas_dimension, GameBoard::flag_color);
                        } else if (game_board[cell_row][cell_col].cover == GameLogic::Board::Cover::Uncovered) {
                            draw_number(cell_canvas, canvas_dimension, GameBoard::mine_color_win, board_controller.get_value(cell_row, cell_col));
                        }
                        cell_canvas.DrawText(2, 1, std::to_string(game_board[cell_row][cell_col].row) + ", " + std::to_string(game_board[cell_row][cell_col].col));
                        return canvas(std::move(cell_canvas));
                    })
                    | Hoverable([cell_row, cell_col, this] (bool is_hovered) {
                        if (is_hovered) {
                            selected_row = cell_row;
                            selected_col = cell_col;
                            //std::cerr << "Hover event at (" << cell_row << ", " << cell_col << ")\n";
                        }
                    })
                };
            }
        }
    }
    void GameBoard::initialize_renderer() {
        Components container_vector;
        for (auto row: game_board) {
            Components row_vector;
            for (auto col: row) {
                row_vector.push_back(col.renderer);
            }
            container_vector.push_back(Container::Horizontal(row_vector));
        }
        renderer = Container::Vertical(container_vector)
        | Renderer([=] (Element e) {
            return e;
        })
        | CatchEvent([=] (Event e) {
            if (game_is_done) {
                // returning true means that this mouse event is consumed by this event catcher
                //  and does not affect any other event catchers
                return true;
            }
            if (e.is_mouse()) {
                mx = e.mouse().x;
                my = e.mouse().y;
                if (e.mouse().motion == Mouse::Released) {
                    //std::cerr << "Catching event at (" << selected_row << ", " << selected_col << ")\n";
                    if (e.mouse().button == Mouse::Left) {
                        game_is_done = board_controller.select(selected_row, selected_col);
                        if (!game_is_done) {
                            for (auto change: board_controller.get_changes()) {
                                game_board[std::get<0>(change)][std::get<1>(change)].cover = GameLogic::Board::Cover::Uncovered;
                            }
                        } else {
                            for (auto mine_loc: board_controller.get_mine_locations()) {
                                if (game_board[mine_loc / width][mine_loc % width].cover != GameLogic::Board::Cover::Flagged) {
                                    game_board[mine_loc / width][mine_loc % width].cover = GameLogic::Board::Cover::Mine;
                                }
                            }
                        }
                    } else if (e.mouse().button == Mouse::Right) {
                        game_is_done = board_controller.flag(selected_row, selected_col);
                        game_board[selected_row][selected_col].cover = board_controller.get_cover(selected_row, selected_col);
                    }
                }
            }
            // returning false means this Mouse event is not consumed by this event catcher
            return false;
        })
        | bgcolor(Color::Black);
    }
    int GameBoard::get_mx() { return mx; }
    int GameBoard::get_my() { return my; }
    int GameBoard::get_selected_row() { return selected_row; }
    int GameBoard::get_selected_col() { return selected_col; }
    void GameBoard::set_canvas_dimension(int new_dimension) {
        canvas_dimension = new_dimension;
    }
    Component GameBoard::get_game_board_renderer() {
        return renderer;
    }
}

#ifdef RUN_UI_TESTS
TEST_SUITE("Game board builder functions") {
    TEST_CASE("Interactive game board test") {
        ScreenInteractive screen = ScreenInteractive::TerminalOutput();
        MESSAGE("Testing game board");

        auto quit_button = Button("End", screen.ExitLoopClosure(), ButtonOption::Animated());
        auto button_container = Container::Vertical({
            quit_button
        });

        GameUI::GameBoard gb {8, 8, 10, 5};
        gb.set_canvas_dimension(12);
        auto gb_renderer = gb.get_game_board_renderer();

        auto renderer = Container::Vertical({
            button_container,
            gb_renderer
        })
        | Renderer([=, &gb] (Element e) {
            return vbox({
                e,
                text("Mouse: " + std::to_string(gb.get_mx()) + ", " + std::to_string(gb.get_my())),
                text("(r, c): " + std::to_string(gb.get_selected_row()) + ", " + std::to_string(gb.get_selected_col()))
            });
        });
        screen.Loop(renderer);
    }
}
#endif