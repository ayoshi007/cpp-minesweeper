#ifndef BOARD_HPP
#define BOARD_HPP

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
        int flag_count {};
        bool lost {};
        bool started {};

        std::mt19937 g { std::random_device{}() };

        std::vector<std::vector<int>> map {};
        std::vector<std::vector<Cover>> visible_map {};
        std::vector<std::pair<int, int>> mine_locations {};
        std::vector<std::pair<int, int>> flag_locations {};

        public:
        Board();
        Board(int mt_seed);
        Board(int w, int h, int mines, int seed);
        Board(int w, int h, int mines);
        void set_board(int w, int h, int mines);
        const std::vector<std::vector<int>>& get_map();
        const std::vector<std::pair<int, int>>& get_mine_locations();
        const std::vector<std::vector<Cover>>& get_visible_map();
        bool select(int x, int y);
        void flag(int x, int y);
    };
}

#endif // BOARD_HPP