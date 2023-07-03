#include <ui/game_board.hpp>
#include <ui/ui_helper.hpp>

#include <doctest/doctest.h>

#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/canvas.hpp>

#include <functional>
#include <vector>
#include <tuple>

using namespace ftxui;

namespace GameUI {
    Color GameBoard::border_color = Color::Blue;
    Color GameBoard::fill_color = Color::DarkBlue;
    Color GameBoard::flag_color = Color::DarkBlue;
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
        for (int r = 0; r < height; r++) {
            std::vector<BoardCell> row;
            for (int c = 0; c < width; c++) {
                BoardCell cell = {
                    r, c,
                    GameLogic::Board::Cover::Covered,
                    nullptr
                };
                cell.renderer = Renderer([=] {
                    Canvas cell_canvas = Canvas(canvas_dimension, canvas_dimension);
                    draw_border(cell_canvas, canvas_dimension, GameBoard::border_color);

                    if (game_board[r][c].cover == GameLogic::Board::Cover::Mine) {
                        Color mine_color = board_controller.is_game_won() ? GameBoard::mine_color_win : GameBoard::mine_color_detonated;
                        draw_mine(cell_canvas, canvas_dimension, mine_color);
                    } else if (game_board[r][c].cover == GameLogic::Board::Cover::Flagged) {
                        draw_flag(cell_canvas, canvas_dimension, GameBoard::flag_color);
                    } else if (game_board[r][c].cover == GameLogic::Board::Cover::Uncovered) {
                        draw_number(cell_canvas, canvas_dimension, GameBoard::mine_color_win, board_controller.get_value(r, c));
                    }
                    //cell_canvas.DrawText(5, 5, std::to_string(game_board[r][c].row) + ", " + std::to_string(game_board[r][c].col));
                    return canvas(std::move(cell_canvas));
                });
                row.push_back(cell);
            }
            game_board.push_back(row);
        }
    }
    void GameBoard::initialize_renderer() {
        container = Container::Vertical({});
        for (auto row: game_board) {
            for (auto col: row) {
                container->Add(col.renderer);
            }
        }
        container |= bgcolor(Color::Black);
        renderer = Renderer(container, [=] {
            std::vector<std::vector<Element>> grid;
            for (int r = 0; r < height; r++) {
                std::vector<Element> row;
                for (int c = 0; c < width; c++) {
                    row.push_back(game_board[r][c].renderer->Render());
                }
                grid.push_back(row);
            }
        
            return vbox({
                gridbox(grid),
                text(std::to_string(mx) + ", " + std::to_string(my)),
                text(std::to_string(selected_row) + ", " + std::to_string(selected_col))
            });
        })
        | CatchEvent([=] (Event e) {
            if (game_is_done) {
                return true;
            }
            if (e.is_mouse()) {
                mx = e.mouse().x;
                my = e.mouse().y;
                
                if (e.mouse().motion == Mouse::Released) {
                    int col = e.mouse().x / (canvas_dimension / 2);
                    int row = e.mouse().y / (canvas_dimension / 4);
                    if (row >= 0 && row < height && col >= 0 && col < width) {
                        selected_col = col;
                        selected_row = row;
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
                return true;
            }
            return false;
        })
        | bgcolor(Color::Black);
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

        GameUI::GameBoard gb {16, 16, 40, 5};

        screen.Loop(gb.get_game_board_renderer());
    }
}
#endif