#ifndef WINDOW
#define WINDOW

#include <ftxui/component/screen_interactive.hpp>
#include <ui/game_board.hpp>
#include <ui/main_menu.hpp>

using namespace ftxui;
namespace GameUI {
    class Window {
        private:
        static std::string title;
        static int board_width;
        static int board_height;
        static int board_mine_count;
        static bool quit_modal_shown;
        static int shown_screen;

        static MainMenu main_menu_components;
        static GameBoard game_board_components;

        static Component quit_button;

        static Component main_renderer;
        static ScreenInteractive screen;

        public:
           static void start();
           static void show_main_menu();
    };
}

#endif // WINDOW

