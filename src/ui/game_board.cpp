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

using namespace ftxui;

namespace GameUI {
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
        canvas_dimension = 12;
        initialize_cells();
        initialize_renderer();
    }
    void GameBoard::initialize_cells() {
        for (int r = 0; r < height; r++) {
            std::vector<BoardCell> row;
            for (int c = 0; c < width; c++) {
                BoardCell cell = {r, c, Color::DarkMagentaBis, Color::Black, nullptr, GameLogic::Board::Cover::Covered};
                cell.renderer = Renderer([=, &game_board] {
                    Canvas cell_canvas = Canvas(canvas_dimension, canvas_dimension);
                    if (game_board[r][c].toggle) {
                        for (int x = 0; x < canvas_dimension; x++) {
                            for (int y = 0; y < canvas_dimension; y++) {
                                cell_canvas.DrawBlock(x, y, true, [=, &game_board] (Pixel& p) {
                                    p.foreground_color = game_board[r][c].fill_color;
                                    p.background_color = game_board[r][c].fill_color;
                                });
                            }
                        }
                    } else {
                        cell_canvas.DrawPointLine(0, 0, canvas_dimension - 1, 0, game_board[r][c].border_color);
                        cell_canvas.DrawPointLine(canvas_dimension - 1, 0, canvas_dimension - 1, canvas_dimension - 1, game_board[r][c].border_color);
                        cell_canvas.DrawPointLine(0, 0, 0, canvas_dimension - 1, game_board[r][c].border_color);
                        cell_canvas.DrawPointLine(0, canvas_dimension - 1, canvas_dimension - 1, canvas_dimension - 1, game_board[r][c].border_color);
                    }
                    cell_canvas.DrawText(5, 5, std::to_string(game_board[r][c].row) + ", " + std::to_string(game_board[r][c].col));
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
        renderer = Renderer(container, [=, &game_board] {
            std::vector<std::vector<Element>> grid;
            for (int r = 0; r < rows; r++) {
                std::vector<Element> row;
                for (int c = 0; c < cols; c++) {
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
        | CatchEvent([=, &game_board] (Event e) {
            if (e.is_mouse()) {
                mx = e.mouse().x;
                my = e.mouse().y;
                selected_col = e.mouse().x / (canvas_dimension / 2);
                selected_row = e.mouse().y / (canvas_dimension / 4);
                return true;
            }
            return false;
        });
    }
}

#ifdef RUN_UI_TESTS
TEST_SUITE("Game board builder functions") {
    TEST_CASE("Interactive game board test" * doctest::skip()) {
        ScreenInteractive screen = ScreenInteractive::TerminalOutput();
        MESSAGE("Testing game board");
    }
}
#endif