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
    class Board {
        public:
        enum Cover {
            Covered,
            Uncovered,
            Flagged
        };
        private:
        int width {};
        int height {};
        int mine_count {};
        int correct_flags {};
        bool lost {};
        bool done {};
        bool started {};

        std::mt19937 g { std::random_device{}() };

        std::vector<std::vector<int>> map {};
        std::vector<std::vector<Cover>> visible_map {};
        std::unordered_set<int> mine_locations {};
        std::vector<std::pair<int, int>> flag_locations {};

        const std::vector<std::pair<int, int>> get_surrounding_positions(int x, int y);
        std::unordered_map<Cover, int> get_visibilities(const std::vector<std::pair<int, int>>& surrounding_positions);
        bool uncover_surroundings(int x, int y);
        std::pair<int, int> find_free_pos(int x, int y);

        public:
        Board();
        Board(int mt_seed);
        Board(int w, int h, int mines, int seed);
        Board(int w, int h, int mines);
        bool is_game_lost();
        bool is_game_done();
        bool is_game_started();
        int get_mine_count();
        int get_correct_flags();
        void clear_board();
        void set_board(int w, int h, int mines);
        
        
        const std::vector<std::vector<int>>& get_map();
        const std::unordered_set<int>& get_mine_locations();
        const std::vector<std::vector<Cover>>& get_visible_map();
        const std::vector<std::vector<std::string>> get_state_map();
        bool select(int x, int y);
        bool flag(int x, int y);
    };
}

#endif // BOARD_HPP