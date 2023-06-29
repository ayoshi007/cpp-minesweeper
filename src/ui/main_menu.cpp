#include <doctest/doctest.h>

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>

#include <ui/main_menu.hpp>
#include <ui/ui_helper.hpp>
#include <core/constants.hpp>

using namespace ftxui;

namespace GameUI {
    std::string MainMenuBuilder::subtitle = "Main menu";
    bool MainMenuBuilder::custom_board_menu_shown = false;
    int MainMenuBuilder::width_slider_value = constants::DEFAULT_CUSTOM_W;
    int MainMenuBuilder::height_slider_value = constants::DEFAULT_CUSTOM_H;
    int MainMenuBuilder::mine_percent_slider_value = constants::DEFAULT_CUSTOM_PERCENT;

    // Component MainMenuBuilder::small_board_button = Button("Small (8x8, 10 mines)", , ButtonOption::Animated());
    // Component MainMenuBuilder::medium_board_button = Button("Medium (16x16, 40 mines)", , ButtonOption::Animated());
    // Component MainMenuBuilder::large_board_button = Button("Large (32x16, 99 mines)", , ButtonOption::Animated());
    Component MainMenuBuilder::build_custom_board_modal() {
        return nullptr;
    }
    Component MainMenuBuilder::build_main_menu_buttons() {
        return nullptr;
    }

    std::string MainMenuBuilder::get_subtitle() {
        return subtitle;
    }
    Component MainMenuBuilder::build_main_menu_renderer() {
        return nullptr;
    }
}

#ifdef RUN_UI_TESTS
TEST_SUITE("Main menu builder functions") {
    
}
#endif