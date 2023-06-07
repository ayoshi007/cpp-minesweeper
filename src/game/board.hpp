#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <utility>

namespace GameLogic {
    class Board {
        private:
        int width;
        int height;
        int mine_count;
        int flagged;
        bool lost;

        std::vector<std::pair<int, int>> mine_locations;
        std::vector<bool> flagged_mines;
    };
}

#endif // BOARD_HPP