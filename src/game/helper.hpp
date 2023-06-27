#ifndef BOARD_HELPER
#define BOARD_HELPER

#include <iostream>
#include <vector>

template <typename T>
void print_map(const std::vector<std::vector<T>>& map) {
    for (auto row: map) {
        for (auto col: row) {
            std::cout << col << '\t';
        }
        std::cout << '\n';
    }
}

#endif // BOARD_HELPER
