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
        const std::unordered_set<int>& get_mine_locations();
        std::unordered_set<int> get_incorrect_flags();

        // called after a successful select
        const std::vector<std::tuple<int, int, int>>& get_changes();

        // debugging
        const std::vector<std::vector<std::string>> get_state_map();
        const std::vector<std::vector<int>>& get_map();
    };
}

#endif // CONTROLLER_HPP