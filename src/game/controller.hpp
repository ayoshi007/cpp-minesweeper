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
        bool select(int x, int y);
        // flags a location and returns if the player won
        bool flag(int x, int y);
        // gets the number of set flags
        int get_flag_count();

        // called in the event of a game over from a select
        std::vector<std::pair<std::pair<int, int>, int>> get_mine_locations();
        std::vector<std::pair<std::pair<int, int>, int>> get_incorrect_flags();

        // called after a successful select
        std::vector<std::pair<std::pair<int, int>, int>> get_changes();
    };
}

#endif // CONTROLLER_HPP