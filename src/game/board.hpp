#ifndef BOARD_HPP
#define BOARD_HPP

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include <random>

namespace GameLogic {
    /**
     * The Board class describes the state of the board and the
     *  logic for manipulating the board, including flagging and 
     *  selecting a cell.
    */
    class Board {
        public:
        /**
         * The Cover enum describes the state of the board
         *  visible to the player
        */
        enum Cover {
            Covered,
            Uncovered,
            Flagged,
            Mine
        };
        private:
        int width {};
        int height {};
        int mine_count {};
        int flag_count {};
        int correct_flag_count {};
        bool lost {};
        bool done {};
        bool started {};

        // the Mersenne Twister is used for randomness
        std::mt19937 g { std::random_device{}() };

        std::vector<std::vector<int>> map {};
        std::vector<std::vector<Cover>> visible_map {};
        std::unordered_set<int> mine_locations {};
        std::unordered_set<int> flag_locations {};
        std::vector<std::tuple<int, int, int>> most_recent_changes {};

        // returns all surrounding coordinates to the input position
        const std::vector<std::pair<int, int>> get_surrounding_positions(int x, int y);
        // returns the number of each Cover given a vector of positions
        std::unordered_map<Cover, int> get_visibilities(const std::vector<std::pair<int, int>>& surrounding_positions);
        // helper functions for select()
        bool select_helper(int x, int y);
        bool uncover_surroundings(int x, int y);
        // randomly finds an unmined position
        std::pair<int, int> find_free_pos();

        public:
        // seeded constructors are included for testability
        Board();
        Board(int mt_seed);
        Board(int w, int h, int mines, int seed);
        Board(int w, int h, int mines);
        int get_width();
        int get_height();
        bool is_game_lost();
        bool is_game_done();
        bool is_game_started();
        int get_flag_count();
        int get_mine_count();
        int get_correct_flag_count();
        void clear_board();
        void set_board(int w, int h, int mines);

        const std::vector<std::vector<int>>& get_map();
        const std::unordered_set<int>& get_mine_locations();
        const std::unordered_set<int>& get_flag_locations();
        const std::vector<std::vector<Cover>>& get_visible_map();
        const std::vector<std::vector<std::string>> get_state_map();
        const std::vector<std::tuple<int, int, int>>& get_most_recent_changes();
        
        bool select(int x, int y);
        bool flag(int x, int y);
    };
}

#endif // BOARD_HPP