#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

namespace GameUI {
    class MainMenu {
        private:
        static bool custom_board_menu_shown;
        static Component small_board_button;
        static Component medium_board_button;
        static Component large_board_button;
        static Component custom_board_button;

        static Component width_slider;
        static Component height_slider;
        static Component mine_percent_slider;
        static Component custom_board_start;
        static Component custom_board_quit;
        static Component custom_board_modal_menu;
 
        public:
        static Component get_main_menu_renderer();
    };
}

#endif // MAIN_MENU_HPP
