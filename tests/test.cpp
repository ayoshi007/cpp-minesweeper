#include <iostream>

#include <game/board.hpp>

void test_set_board() {
    GameLogic::Board board {5, 5, 5};
    const std::vector<std::vector<int>>& map1 = board.get_map();

    for (auto row: map1) {
        for (auto col: row) {
            std::cout << col << '\t';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    board.set_board(8, 8, 10);
    const std::vector<std::vector<int>>& map2 = board.get_map();

    for (auto row: map2) {
        for (auto col: row) {
            std::cout << col << '\t';
        }
        std::cout << '\n';
    }
}

int main() {
    test_set_board();
    return 0;
}