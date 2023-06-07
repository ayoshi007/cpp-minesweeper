#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>

#include <ui/main_menu.hpp>
#include <ui/ui_helper.hpp>
#include <core/constants.hpp>

using namespace ftxui;

std::string GameUI::MainMenu::subtitle = "Main menu";
// Component GameUI::MainMenu::small_board_button = Button("Small (8x8, 10 mines)", , ButtonOption::Animated());
// Component GameUI::MainMenu::medium_board_button = Button("Medium (16x16, 40 mines)", , ButtonOption::Animated());
// Component GameUI::MainMenu::large_board_button = Button("Large (32x16, 99 mines)", , ButtonOption::Animated());

GameUI::MainMenu::MainMenu() :
    custom_board_menu_shown {false},
    width_slider_value { constants::DEFAULT_CUSTOM_W },
    height_slider_value { constants::DEFAULT_CUSTOM_H },
    mine_percent_slider_value { constants::DEFAULT_CUSTOM_PERCENT }
    {

}

std::string GameUI::MainMenu::get_subtitle() {
    return subtitle;
}
