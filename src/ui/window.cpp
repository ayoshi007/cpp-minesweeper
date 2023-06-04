#include <ui/window.hpp>

#include <core/constants.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>

std::string GameUI::Window::title = "TUI Minesweeper";
int GameUI::Window::board_width = constants::DEFAULT_CUSTOM_W;
int GameUI::Window::board_height = constants::DEFAULT_CUSTOM_H;
int GameUI::Window::board_mine_count = constants::SMALL_BOARD_MINES;
bool GameUI::Window::quit_modal_shown = false;
int GameUI::Window::shown_screen = constants::MAIN_MENU_SCREEN;
ScreenInteractive GameUI::Window::screen = ScreenInteractive::TerminalOutput();

int GameUI::Window::get_width() {
    return board_width;
}
int GameUI::Window::get_height() {
    return board_height;
}
int GameUI::Window::get_mine_count() {
    return board_mine_count;
}
int GameUI::Window::get_shown_screen() {
    return shown_screen;
}