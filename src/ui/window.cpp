#include <my_minesweeper/constants.hpp>
#include <my_minesweeper/ui/ui_control.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>

using namespace ftxui;
namespace GameUI {
    extern const ScreenInteractive screen = ScreenInteractive::TerminalOutput();
    extern const exit_game = ScreenInteractive::Active()->ExitLoopClosure();
    extern const std::string title = "TUI Minesweeper";

    extern const bool quit_modal_shown = false;
    extern const auto show_quit_modal = [] { quit_modal_shown = true; };

    Component create_window_bar_renderer(const std::string& title, const std::string& subtitle, Component quit_button) {
        return quit_button
            | Renderer([title, subtitle](Element button) {
                return hbox({
                    text(title) | center,
                    separator(),
                    text(subtitle) | flex,
                    button
            });
        });
    }
    Component create_yes_no_modal_renderer(const std::string& prompt, std::function<void()> yesOp, std::function<void()> noOp) {
        return Container::Vertical({
            Button("Yes", yesOp, ButtonOption::Animated()),
            Button("No", noOp, ButtonOption::Animated())
        })
        | Renderer([prompt](Element buttons) {
            return vbox({
                text(prompt),
                separator(),
                buttons
            })
            | border | bgcolor(Color::Black);
        });
    }

    extern const Component quit_button = Button("Quit", show_quit_modal, ButtonOption::Ascii());

    main_menu_renderer = 

    shown_screen = constants::MAIN_MENU_SCREEN;
    board_width = constants::SMALL_BOARD_WIDTH;
    board_height = constants::SMALL_BOARD_HEIGHT;
    mine_count = constants::SMALL_BOARD_MINES;

}