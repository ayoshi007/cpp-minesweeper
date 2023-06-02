#ifndef UI_CONTROL
#define UI_CONTROL

#include <functional>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

// declare all components, variables, and functors that affect the state of the UI here
using namespace ftxui;
namespace GameUI {
    ScreenInteractive screen;
    int shown_screen;
    std::function<void()> exit_game;
    int boardWidth;
    int boardHeight;
    int mineCount;

    std::string title;
    Component window_bar;
    Component create_window_bar_renderer(std::string subtitle);
    bool quit_modal_shown;
    Component quit_button;
    Component quit_modal;
    std::function<void()> show_quit_modal;
    std::function<void()> hide_quit_modal;

    std::function<void()> show_main_menu;
    std::function<void()> show_game_board;
    Component main_menu_renderer;
    Component game_board_renderer;
    // Container to hold the main menu and game board renderers
    Component screens;
    // the main renderer
    Component main_renderer;
}

#endif // UI_CONTROL

