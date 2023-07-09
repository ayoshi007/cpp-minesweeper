#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <functional>
#include <ftxui/component/component.hpp>


namespace GameUI {
    class MainMenuBuilder {
        private:
        static std::function<void()> small_board_button_action;
        static std::function<void()> med_board_button_action;
        static std::function<void()> large_board_button_action;
        static std::function<void()> custom_board_button_action;

        static int width_slider_value;
        static int height_slider_value;
        static int mine_percent_slider_value;

        static ftxui::Component build_custom_board_modal(std::function<void()> custom_board_action);
        static ftxui::Component build_main_menu_buttons(
            std::function<void()> small_board_action,
            std::function<void()> med_board_action,
            std::function<void()> large_board_action
        );

        public:
        static bool custom_board_menu_shown;
        static int get_width_slider_value();
        static int get_height_slider_value();
        static int get_mine_percent_slider_value();

        static ftxui::Component build_main_menu_renderer(
            std::function<void()> small_board_action,
            std::function<void()> med_board_action,
            std::function<void()> large_board_action,
            std::function<void()> custom_board_action
        );
    };
}

#endif // MAIN_MENU_HPP
