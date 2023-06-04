#ifndef WINDOW
#define WINDOW

#include <ftxui/component/screen_interactive.hpp>
#include <ui/game_board.hpp>
#include <ui/main_menu.hpp>

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

        static Component main_renderer;
        static ScreenInteractive screen;

        public:
        static int get_width();
        static int get_height();
        static int get_mine_count();
        static int get_shown_screen();

    };
}

#endif // WINDOW

