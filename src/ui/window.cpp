#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>

#include <ui/window.hpp>
#include <ui/ui_helper.hpp>
#include <core/constants.hpp>

using namespace ftxui;

namespace GameUI {
    std::string Window::title = "TUI Minesweeper";
    std::string Window::current_subtitle = "Subtitle";
    int Window::board_width = constants::DEFAULT_CUSTOM_W;
    int Window::board_height = constants::DEFAULT_CUSTOM_H;
    int Window::board_mine_count = constants::SMALL_BOARD_MINES;
    bool Window::quit_modal_shown = false;
    int Window::shown_screen = constants::MAIN_MENU_SCREEN;
    ScreenInteractive Window::screen = ScreenInteractive::TerminalOutput();
    Component Window::quit_button = Button(
        "Quit",
        [] { quit_modal_shown = true; },
        ButtonOption::Ascii()
        );

    void Window::start() {
        current_subtitle = MainMenuBuilder::get_subtitle();
        Component quit_modal = PartsBuilder::build_modal_prompt(
            "Quit?",
            Window::screen.ExitLoopClosure(),
            [](){ Window::quit_modal_shown = false; }
            );
        Component window_bar_renderer = Renderer(quit_button, [](){
            return hbox({
                PartsBuilder::build_text_element(Window::title) | center,
                separator(),
                PartsBuilder::build_text_element(current_subtitle) | flex,
                Window::quit_button->Render()
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
    void Window::show_main_menu() {
        Window::shown_screen = constants::MAIN_MENU_SCREEN;
    }
}