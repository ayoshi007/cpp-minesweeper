#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <functional>
#include <ftxui/component/component.hpp>

using namespace ftxui;
namespace GameUI {
    class MainMenu {
        private:
        static std::string subtitle;
        static bool custom_board_menu_shown;

        static Component small_board_button;
        static std::function<void()> small_board_action;
        static Component medium_board_button;
        static std::function<void()> medium_board_action;
        static Component large_board_button;
        static std::function<void()> large_board_action;

        static int width_slider_value;
        static Component width_slider;
        static int height_slider_value;
        static Component height_slider;
        static int mine_percent_slider_value;
        static Component mine_percent_slider;

        static Component custom_board_button;
        static Component custom_board_start;
        static Component custom_board_quit;
        static std::function<void()> custom_board_action;
        static Component custom_board_modal_menu;
 
        public:
        static std::string get_subtitle();
        static Component build_board_button(int& width, int& height, int& mine_count, std::function<void()> action);
        static Component get_main_menu_renderer();
    };
}

#endif // MAIN_MENU_HPP
