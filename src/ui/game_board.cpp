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
    /*
    std::function<void(ftxui::Canvas&, int, ftxui::Color)> GameBoard::draw_flag = [] (Canvas& canvas, int dimension, Color color) {
        
    };
    std::function<void(ftxui::Canvas&, int, ftxui::Color)> GameBoard::draw_mine = [] (Canvas& canvas, int dimension, Color color) {
        
    };
    std::function<void(ftxui::Canvas&, int, ftxui::Color)> GameBoard::draw_number = [] (Canvas& canvas, int dimension, Color color) {
        
    };
    */

    GameBoard::GameBoard(int w, int h, int mines) : 
        width {w},
        height {h},
        mx {},
        my {},
        selected_row {},
        selected_col {},
        mine_count {mines},
        board_controller {}
        {
        board_controller.initialize_board(w, h, mines);
        canvas_dimension = 48;
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
            if (e.is_mouse()) {
                mx = e.mouse().x;
                my = e.mouse().y;
                if (e.mouse().motion == Mouse::Released) {
                    int col = e.mouse().x / (canvas_dimension / 2);
                    int row = e.mouse().y / (canvas_dimension / 4);
                    if (row >= 0 && row < height && col >= 0 && col < width) {
                        selected_col = col;
                        selected_row = row;
                        /*
                        if (e.mouse().button == Mouse::Left) {
                            bool detonated = board_controller.select(selected_row, selected_col);
                            if (!detonated) {
                                for (auto change: board_controller.get_changes()) {
                                    
                                }
                            } else {

                            }
                        } else if (e.mouse().button == Mouse::Right) {
                            bool won = board_controller.flag(selected_row, selected_col);
                        }
                        */
                    }
                }
                return true;
            }
            return false;
        });
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

        GameUI::GameBoard gb {2, 1, 1};

        screen.Loop(gb.get_game_board_renderer());
    }
}
#endif