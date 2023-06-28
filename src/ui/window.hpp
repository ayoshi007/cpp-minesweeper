#ifndef WINDOW
#define WINDOW

#include <ftxui/component/screen_interactive.hpp>
#include <ui/game_board.hpp>
#include <ui/main_menu.hpp>

namespace GameUI {
    class Window {
        private:
        static std::string title;
        static std::string current_subtitle;
        static int board_width;
        static int board_height;
        static int board_mine_count;
        static bool quit_modal_shown;
        static int shown_screen;

        static MainMenuBuilder main_menu_components;
        static GameBoard game_board_components;

        static ftxui::Component quit_button;

        static ftxui::Component main_renderer;
        static ftxui::ScreenInteractive screen;

        public:
           static void start();
           static void show_main_menu();
    };
}

#endif // WINDOW

