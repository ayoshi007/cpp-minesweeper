#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <vector>
#include <tuple>
#include <utility>

#include <game/board.hpp>

namespace GameLogic {
    class BoardController {
        private:
        Board board;

        public:
        void set_board(int w, int h, int mines);
        std::vector<std::tuple<int, int, int>> reveal(int x, int y);
        std::vector<std::pair<int, int>> get_mine_locations();
    };
}

#endif // CONTROLLER_HPP