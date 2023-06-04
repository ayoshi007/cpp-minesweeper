#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <functional>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/element.hpp>

// define all components and elements of main menu here
using namespace ftxui;
namespace GameUI {
    namespace MainMenu {
        int chosen_width;
        int chosen_height;
        int chosen_mine_count;
        bool board_chosen;
        int mine_percent;
        bool custom_board_modal_shown;

        std::function<void()> create_small_board;
        std::function<void()> create_medium_board;
        std::function<void()> create_large_board;
        std::function<void()> create_custom_board;
        std::function<void()> show_custom_board_modal;
        std::function<void()> hide_custom_board_modal;

        std::function<Element(const std::string&, int)> slider_label;

        Component small_board_button;
        Component medium_board_button;
        Component large_board_button;
        Component custom_board_button;

        Component width_slider;
        Component height_slider;
        Component mine_percent_slider;
        Component custom_board_start;
        Component custom_board_quit;
        Component custom_board_modal_component;

        Component main_menu_buttons;
        
        Component custom_board_modal_renderer;
        Component main_menu_buttons_renderer;
    }
}

#endif // MAIN_MENU_HPP
