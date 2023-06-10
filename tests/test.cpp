#include <iostream>

#include <game/board.hpp>

GameLogic::Board board {5}; // seed = 1

template <typename T>
void print_map(const std::vector<std::vector<T>>& map) {
    for (auto row: map) {
        for (auto col: row) {
            std::cout << col << '\t';
        }
        std::cout << '\n';
    }
}
void test_set_board(int w, int h, int mines) {
    std::cout << "Setting board with w = " + std::to_string(w) + ", h = " + std::to_string(h) + ", mines = " + std::to_string(mines) + "\n";
    board.set_board(w, h, mines);
    print_map(board.get_map());
}
void test_flag(int x, int y) {
    std::cout << "Flagging cell at x = " + std::to_string(x) + ", y = " + std::to_string(y) + "\n";
    board.flag(x, y);
    print_map(board.get_state_map());
}
void test_select(int x, int y) {
    std::cout << "Selecting cell at at x = " + std::to_string(x) + ", y = " + std::to_string(y) + "\n";
    bool detonation = board.select(x, y);
    print_map(board.get_state_map());
    if (detonation) {
        std::cout << "You detonated a mine\n";
    }
}

int main() {
    std::cout << "Showing test output for seeded board generation\n";
    test_set_board(5, 5, 5);
    test_select(4, 2);
    test_select(4, 4);
    test_select(3, 4);

    std::cout << "\nTesting a 8x8 board with 10 mines\n";
    test_set_board(8, 8, 10);
    test_select(0, 4);
    print_map(board.get_map());
    
    return 0;
}