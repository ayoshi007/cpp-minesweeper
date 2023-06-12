#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <game/board.hpp>

namespace GameLogic {
    /**
     * A class to interface with a Board instance
    */
    class BoardController {
        private:
        Board board;

        public:
        BoardController();
        bool initialize_board(int width, int height, int mine_count);
        bool select(int x, int y);
        bool flag(int x, int y);
        int get_flag_count();
    };
}

#endif // CONTROLLER_HPP