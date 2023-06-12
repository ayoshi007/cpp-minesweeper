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

        MainMenu();
        // Component build_main_menu_renderer(const std::string& label, std::function<void()> action);
        // Component build_slider_and_label(int value)
    };
}

#endif // MAIN_MENU_HPP
