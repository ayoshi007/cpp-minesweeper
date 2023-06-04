#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <functional>
#include <ftxui/component/component.hpp>

// define all components and elements of main menu here
using namespace ftxui;
namespace GameUI {
    namespace MainMenu {
        std::string subtitle;
        std::function<void()> create_small_board;
        std::function<void()> create_medium_board;
        std::function<void()> create_large_board;
        std::function<void()> create_custom_board;
        int mine_percent;
        bool custom_board_modal_shown;
        std::function<void()> show_custom_board_modal;
        std::function<void()> hide_custom_board_modal;
        std::function<Component(std::string, int)> slider_label;

        Component small_board_button;
        Component medium_board_button;
        Component large_board_button;
        Component custom_board_button;
        Component main_menu_buttons;

        Component width_slider;
        Component height_slider;
        Component mine_percent_slider;
        Component custom_board_start;
        Component custom_board_quit;
        Component custom_board_modal;
    }
}

#endif // MAIN_MENU_HPP
