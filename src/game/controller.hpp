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
        bool initialize_board(int width, int height, int mine_count, int seed);
        bool initialize_board(int width, int height, int mine_count);
        // selects a location on the board and returns all uncovered spots
        // includes any uncovered mines (with value -1)
        std::vector<std::pair<std::pair<int, int>, int>> select(int x, int y);
        // flags a location and returns if the player won
        bool flag(int x, int y);
        // gets the number of set flags
        int get_flag_count();
        // gets all mine locations (only returns when the game is lost)
        std::vector<std::pair<int, int>> get_mine_locations();
    };
}

#endif // CONTROLLER_HPP