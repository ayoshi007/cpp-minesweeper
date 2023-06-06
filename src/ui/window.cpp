#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>

#include <ui/window.hpp>
#include <ui/ui_helper.hpp>
#include <core/constants.hpp>

using namespace ftxui;

std::string GameUI::Window::title = "TUI Minesweeper";
int GameUI::Window::board_width = constants::DEFAULT_CUSTOM_W;
int GameUI::Window::board_height = constants::DEFAULT_CUSTOM_H;
int GameUI::Window::board_mine_count = constants::SMALL_BOARD_MINES;
bool GameUI::Window::quit_modal_shown = false;
int GameUI::Window::shown_screen = constants::MAIN_MENU_SCREEN;
ScreenInteractive GameUI::Window::screen = ScreenInteractive::TerminalOutput();
Component GameUI::Window::quit_button = Button(
    "Quit",
    [] { quit_modal_shown = true; },
    ButtonOption::Ascii()
    );

void GameUI::Window::start() {
    Component quit_modal = GameUI::ModalPromptBuilder::build(
        "Quit?",
        GameUI::Window::screen.ExitLoopClosure(),
        [](){ GameUI::Window::quit_modal_shown = false; }
        );
    Component window_bar_renderer = Renderer(quit_button, [](){
        return hbox({
            text(GameUI::Window::title) | center,
            separator(),
            text("subtitle placeholder") | flex,
            GameUI::Window::quit_button->Render()
        });
    });
    //Component tabs = Container::Tab
    Component main_component = Container::Vertical({
        window_bar_renderer
    });
    Component main_renderer = Renderer(main_component, [&](){
        return vbox({
            main_component->Render()
        });
    })
    | Modal(quit_modal, &quit_modal_shown)
    | border;
    screen.Loop(main_renderer);
}
void GameUI::Window::show_main_menu() {
    GameUI::Window::shown_screen = constants::MAIN_MENU_SCREEN;
}