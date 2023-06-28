#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <functional>
#include <ftxui/component/component.hpp>


namespace GameUI {
    class MainMenu {
        private:
        static std::string subtitle;

        bool custom_board_menu_shown;
        int width_slider_value;
        int height_slider_value;
        int mine_percent_slider_value;

        public:
        static std::string get_subtitle();

        static ftxui::Component build_main_menu_renderer();
    };
}

#endif // MAIN_MENU_HPP
