#include <iostream>

#include <game/board.hpp>

GameLogic::Board board {5}; // seed = 1

void print_map() {
    const std::vector<std::vector<int>>& map = board.get_map();

    for (auto row: map) {
        for (auto col: row) {
            std::cout << col << '\t';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
void print_visible_map() {
    const std::vector<std::vector<GameLogic::Board::Cover>>& map = board.get_visible_map();

    for (auto row: map) {
        for (auto col: row) {
            std::cout << col << '\t';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
void print_state_map() {
    const std::vector<std::vector<std::string>>& map = board.get_state_map();

    for (auto row: map) {
        for (auto col: row) {
            std::cout << col << '\t';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
void test_set_board(int w, int h, int mines) {
    std::cout << "Setting board with w = " + std::to_string(w) + ", h = " + std::to_string(h) + ", mines = " + std::to_string(mines) + "\n";
    board.set_board(w, h, mines);
    print_map();
}
void test_flag(int x, int y) {
    std::cout << "Flagging board at x = " + std::to_string(x) + ", y = " + std::to_string(y) + "\n";
    board.flag(x, y);
    print_state_map();
}

int main() {
    std::cout << "Showing test output for seeded board generation\n";
    test_set_board(5, 5, 5);
    test_flag(0, 0);
    test_flag(0, 1);
    test_flag(0, 0);
    
    return 0;
}