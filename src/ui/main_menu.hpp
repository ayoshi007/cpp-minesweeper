#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <functional>
#include <ftxui/component/component.hpp>


namespace GameUI {
    class MainMenuBuilder {
        private:
        static std::string subtitle;

        static std::string small_button_text;
        static std::string med_button_text;
        static std::string large_button_text;
        static std::string custom_button_text;


        static bool custom_board_menu_shown;
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
        static std::string get_subtitle();

        static ftxui::Component build_main_menu_renderer(
            std::function<void()> small_board_action,
            std::function<void()> med_board_action,
            std::function<void()> large_board_action,
            std::function<void()> custom_board_action
        );
    };
}

#endif // MAIN_MENU_HPP
