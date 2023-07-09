#ifndef WINDOW
#define WINDOW

#include <ui/game_board.hpp>
#include <ui/main_menu.hpp>

#include <ftxui/component/screen_interactive.hpp>

#include <vector>
#include <memory>

/*
CHANGE IMPLEMENTATION TO USE 'NESTED' SCREENS!
*/

namespace GameUI {
    class Window {
        private:
        static bool quit_modal_shown;
        
        static ftxui::ScreenInteractive main_menu_screen;
        static ftxui::ScreenInteractive game_board_screen;

        static int get_cell_dimension(int width, int height);
        static void show_main_menu();
        static void show_game(int width, int height, int mine_count, int dimension);

        public:
        static void start();
    };
}

#endif // WINDOW

