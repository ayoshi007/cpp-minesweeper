#include <doctest/doctest.h>

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>

#include <ui/main_menu.hpp>
#include <ui/ui_helper.hpp>
#include <core/constants.hpp>

using namespace ftxui;

namespace GameUI {
    std::string MainMenu::subtitle = "Main menu";
    bool MainMenu::custom_board_menu_shown = false;
    int MainMenu::width_slider_value = constants::DEFAULT_CUSTOM_W;
    int MainMenu::height_slider_value = constants::DEFAULT_CUSTOM_H;
    int MainMenu::mine_percent_slider_value = constants::DEFAULT_CUSTOM_PERCENT;

    // Component MainMenu::small_board_button = Button("Small (8x8, 10 mines)", , ButtonOption::Animated());
    // Component MainMenu::medium_board_button = Button("Medium (16x16, 40 mines)", , ButtonOption::Animated());
    // Component MainMenu::large_board_button = Button("Large (32x16, 99 mines)", , ButtonOption::Animated());


    std::string MainMenu::get_subtitle() {
        return subtitle;
    }
    Component MainMenu::build_main_menu_renderer() {
        return nullptr;
    }
}
