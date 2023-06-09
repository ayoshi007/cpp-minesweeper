#include <numeric>
#include <algorithm>
#include <random>
#include <game/board.hpp>

GameLogic::Board::Board() = default;
GameLogic::Board::Board(int mt_seed) : Board{} {
    g.seed(mt_seed);
}
GameLogic::Board::Board(int w, int h, int mines, int mt_seed) : Board{w, h, mines} {
    g.seed(mt_seed);
}
GameLogic::Board::Board(int w, int h, int mines) :
    flag_count { 0 },
    lost { false },
    started { false },
    map {},
    visible_map {},
    mine_locations {},
    flag_locations {}
    {
    set_board(w, h, mines);
}
void GameLogic::Board::set_board(int w, int h, int mines) {
    map.clear();
    visible_map.clear();
    mine_locations.clear();
    flag_locations.clear();

    width = w;
    height = h;
    mine_count = mines;
    for (int r{}; r < h; r++) {
        map.push_back(std::vector<int> (w));
        visible_map.push_back(std::vector<Cover> (w));
    }
    std::vector<int> positions (w * h);
    
    std::iota(positions.begin(), positions.end(), 0);
    
    std::shuffle(positions.begin(), positions.end(), g);
    for (int i{}; i < mines; i++) {
        int mine_pos = positions[i];
        int r = mine_pos / w;
        int c = mine_pos % w;
        map[r][c] = -1;
        visible_map[r][c] = Cover::Covered;
        mine_locations.push_back(std::pair<int, int> {r, c});
        if (r != 0) {
            if (c != 0) {
                map[r - 1][c - 1] = map[r - 1][c - 1] == -1 ? map[r - 1][c - 1] : map[r - 1][c - 1] + 1;
            }
            if (c != w - 1) {
                map[r - 1][c + 1] = map[r - 1][c + 1] == -1 ? map[r - 1][c + 1] : map[r - 1][c + 1] + 1;
            }
            map[r - 1][c] = map[r - 1][c] == -1 ? map[r - 1][c] : map[r - 1][c] + 1;
        }
        if (r != h - 1) {
            if (c != 0) {
                map[r + 1][c - 1] = map[r + 1][c - 1] == -1 ? map[r + 1][c - 1] : map[r + 1][c - 1] + 1;
            }
            if (c != w - 1) {
                map[r + 1][c + 1] = map[r + 1][c + 1] == -1 ? map[r + 1][c + 1] : map[r + 1][c + 1] + 1;
            }
            map[r + 1][c] = map[r + 1][c] == -1 ? map[r + 1][c] : map[r + 1][c] + 1;
        }
        if (c != 0) {
            map[r][c - 1] = map[r][c - 1] == -1 ? map[r][c - 1] : map[r][c - 1] + 1;
        }
        if (c != w - 1) {
            map[r][c + 1] = map[r][c + 1] == -1 ? map[r][c + 1] : map[r][c + 1] + 1;
        }
    }
}
const std::vector<std::vector<int>>& GameLogic::Board::get_map() {
    return map;
}
const std::vector<std::vector<GameLogic::Board::Cover>>& GameLogic::Board::get_visible_map() {
    return visible_map;
}
const std::vector<std::pair<int, int>>& GameLogic::Board::get_mine_locations() {
    return mine_locations;
}
bool GameLogic::Board::select(int x, int y) {
    
}
void GameLogic::Board::flag(int x, int y) {
    switch (visible_map[x][y]) {
        case Cover::Covered:
            visible_map[x][y] = Cover::Flagged;
            break;
        case Cover::Uncovered:
            break;
        case Cover::Flagged:
            visible_map[x][y] = Cover::Covered;
            break;
    }
}