#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <functional>
#include <ftxui/component/component.hpp>


namespace GameUI {
    class MainMenu {
        private:
        static std::string subtitle;

        static bool custom_board_menu_shown;
        static int width_slider_value;
        static int height_slider_value;
        static int mine_percent_slider_value;

        public:
        static std::string get_subtitle();

        static ftxui::Component build_main_menu_renderer();
    };
}

#endif // MAIN_MENU_HPP
