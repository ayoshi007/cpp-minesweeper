#include <ui/window.hpp>
#include <ui/ui_helper.hpp>
#include <ui/game_board.hpp>
#include <ui/main_menu.hpp>
#include <core/constants.hpp>

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>

#include <algorithm>
#include <vector>
#include <memory>
#include <cmath>

using namespace ftxui;

namespace GameUI {
    bool Window::quit_modal_shown {false};
    
    ScreenInteractive Window::main_menu_screen = ScreenInteractive::Fullscreen();
    ScreenInteractive Window::game_board_screen = ScreenInteractive::Fullscreen();
    
    int Window::get_cell_dimension(int width, int height) {
        int smaller_screen_dim = main_menu_screen.dimx() < main_menu_screen.dimy() ? main_menu_screen.dimx() : main_menu_screen.dimy();
        int smaller_board_dim = main_menu_screen.dimx() < main_menu_screen.dimy() ? width : height;

        int dimension = smaller_screen_dim / (smaller_board_dim + 1) * 4;
        return dimension == 0 ? 1 : dimension;
    }
    void Window::show_main_menu() {
        quit_modal_shown = false;
        MainMenuBuilder::custom_board_menu_shown = false;
        Component quit_button = Button("Quit", [] { quit_modal_shown = true; }, ButtonOption::Ascii());
        Component quit_modal = PartsBuilder::build_modal_prompt(
            "Exit TUI Minesweeper?",
            Window::main_menu_screen.ExitLoopClosure(),
            [](){ Window::quit_modal_shown = false; }
        );
        Component window_bar_renderer = Renderer(quit_button, [=](){
            return hbox({
                PartsBuilder::build_text_element(constants::WINDOW_TITLE) | center,
                separator(),
                PartsBuilder::build_text_element(constants::MAIN_MENU_SUBTITLE) | flex,
                quit_button->Render()
            });
        });
        Component main_menu_renderer = MainMenuBuilder::build_main_menu_renderer(
            [] {
                main_menu_screen.ExitLoopClosure()();
                
                int dimension = get_cell_dimension(constants::SMALL_BOARD_W, constants::SMALL_BOARD_H);

                std::cerr << "=== Generating small board ===\n";
                std::cerr << main_menu_screen.dimx() << ", " << main_menu_screen.dimy() << "\n";
                std::cerr << dimension << "\n";
                std::cerr << "==============================\n";

                show_game(
                    constants::SMALL_BOARD_W,
                    constants::SMALL_BOARD_H,
                    constants::SMALL_BOARD_MINES,
                    dimension
                );
            },
            [] {
                main_menu_screen.ExitLoopClosure()();
                int dimension = get_cell_dimension(constants::MED_BOARD_W, constants::MED_BOARD_H);
                show_game(
                    constants::MED_BOARD_W,
                    constants::MED_BOARD_H,
                    constants::MED_BOARD_MINES,
                    dimension
                );
            },
            [] {
                main_menu_screen.ExitLoopClosure()();
                int dimension = get_cell_dimension(constants::LARGE_BOARD_W, constants::LARGE_BOARD_H);
                show_game(
                    constants::LARGE_BOARD_W,
                    constants::LARGE_BOARD_H,
                    constants::LARGE_BOARD_MINES,
                    dimension
                );
            },
            [] {
                main_menu_screen.ExitLoopClosure()();
                int board_width = GameUI::MainMenuBuilder::get_width_slider_value();
                int board_height = GameUI::MainMenuBuilder::get_height_slider_value();
                int mine_percent = GameUI::MainMenuBuilder::get_mine_percent_slider_value();
                int board_mine_count = board_width * board_height * mine_percent / 100;
                if (board_mine_count == 0) {
                    board_mine_count += 2;
                } else if (board_width * board_height - 10 < board_mine_count) {
                    board_mine_count = board_width * board_height - 10;
                }
                int dimension = get_cell_dimension(board_width, board_height);

                std::cerr << "=== Generating custom board ===\n";
                std::cerr << board_width << "x" << board_height << "\n";
                std::cerr << main_menu_screen.dimx() << ", " << main_menu_screen.dimy() << "\n";
                std::cerr << dimension << "\n";
                std::cerr << "===============================\n";

                show_game(
                    board_width,
                    board_height,
                    board_mine_count,
                    dimension
                );
            }
        );
        Component container = Container::Vertical({
            window_bar_renderer,
            main_menu_renderer
        });
        Component renderer = Renderer(container, [&](){
            return vbox({
                window_bar_renderer->Render(),
                separator(),
                main_menu_renderer->Render()
            });
        })
        | Modal(quit_modal, &quit_modal_shown)
        | border
        | bgcolor(Color::Black);

        main_menu_screen.Loop(renderer);
    }
    void Window::show_game(int width, int height, int mine_count, int dimension) {
        quit_modal_shown = false;
        Component quit_button = Button("Quit", [] { quit_modal_shown = true; }, ButtonOption::Ascii());
        Component quit_modal = PartsBuilder::build_modal_prompt(
            "Exit TUI Minesweeper?",
            Window::game_board_screen.ExitLoopClosure(),
            [](){ Window::quit_modal_shown = false; }
        );
        Component window_bar_renderer = Renderer(quit_button, [=](){
            return hbox({
                PartsBuilder::build_text_element(constants::WINDOW_TITLE) | center,
                separator(),
                PartsBuilder::build_text_element(constants::GAME_BOARD_SUBTITLE) | flex,
                quit_button->Render()
            });
        });
        GameBoard gb {width, height, mine_count, dimension};
        Component change_difficulty_button = Button(
            "Change difficulty",
            [] {
                game_board_screen.ExitLoopClosure()();
                show_main_menu();
            },
            ButtonOption::Animated()
        );
        Component gb_renderer = gb.get_game_board_renderer();
        Component new_game_button = gb.get_new_game_button();
        Component container = Container::Vertical({
            window_bar_renderer,
            gb_renderer,
            new_game_button,
            change_difficulty_button
        });
        Component renderer = Renderer(container, [=, &gb] () {
            return vbox({
                window_bar_renderer->Render(),
                separator(),
                hbox({
                    filler(), gb_renderer->Render() | center , filler(), separator(),
                    vbox({
                        hbox({filler(), gb.get_flag_label(), filler()}) | border | xflex,
                        filler(),
                        new_game_button->Render(),
                        change_difficulty_button->Render()
                    })
                }) | yflex
            });
        })
        | Modal(quit_modal, &quit_modal_shown)
        | border
        | bgcolor(Color::Black);

        game_board_screen.Loop(renderer);
    }
    void Window::start() {
        show_main_menu();
    }
}