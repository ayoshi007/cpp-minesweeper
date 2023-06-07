#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <tuple>
#include <utility>

namespace GameLogic {
    class Board {
        private:
        int width {};
        int height {};
        int mine_count {};
        int flagged {};
        bool lost {};
        bool started {};

        std::vector<std::vector<int>> map;
        std::vector<std::vector<int>> visible_map;
        std::vector<std::pair<int, int>> mine_locations;
        std::vector<std::pair<int, int>> flag_locations;

        public:
        Board(int w, int h, int mines);
        void set_board(int w, int h, int mines);
        const std::vector<std::vector<int>>& get_map();
        const std::vector<std::pair<int, int>>& get_mine_locations();
        // std::vector<std::tuple<int, int, int>> select(int x, int y);
    };
}

#endif // BOARD_HPP