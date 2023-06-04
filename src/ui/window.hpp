#ifndef UI_CONTROL
#define UI_CONTROL

#include <functional>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

// declare all components, variables, and functors that affect the state of the UI here
using namespace ftxui;
namespace GameUI {
    extern const ScreenInteractive screen;
    extern const std::function<void()> exit_game;
    extern const std::string title;

    bool quit_modal_shown;
    extern const std::function<void()> show_quit_modal;
    extern const std::function<void()> hide_quit_modal;
    extern const std::function<void()> show_main_menu;
    extern const std::function<void()> show_game_board;

    extern const Component quit_button;

    Component create_window_bar_renderer(const std::string& title, const std::string& subtitle, Component quit_button);
    Component create_yes_no_modal_renderer(const std::string& prompt, std::function<void()> yesOp, std::function<void()> noOp);
    
    extern const Component main_menu_renderer;
    // Container to hold the main menu and game board renderers
    Component screens;
    // the main renderer
    Component main_renderer;

    int shown_screen;
    int board_width;
    int board_height;
    int mine_count;
}

#endif // UI_CONTROL

