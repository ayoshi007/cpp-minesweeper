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
    correct_flags { 0 },
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
        const std::vector<std::pair<int, int>> surrounding_positions = get_surrounding_positions(r, c);
        for (auto pos: surrounding_positions) {
            map[pos.first][pos.second] = map[pos.first][pos.second] == -1 ? map[pos.first][pos.second] : map[pos.first][pos.second] + 1;
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
const std::vector<std::pair<int, int>> GameLogic::Board::get_surrounding_positions(int x, int y) {
    std::vector<std::pair<int, int>> surrounding_positions;
    
    if (x != 0) {
        if (y != 0) {
            surrounding_positions.push_back(std::pair<int, int> {x - 1, y - 1});
        }
        if (y != width - 1) {
            surrounding_positions.push_back(std::pair<int, int> {x - 1, y + 1});
        }
        surrounding_positions.push_back(std::pair<int, int> {x - 1, y});
    }
    if (x != height - 1) {
        if (y != 0) {
            surrounding_positions.push_back(std::pair<int, int> {x + 1, y - 1});
        }
        if (y != width - 1) {
            surrounding_positions.push_back(std::pair<int, int> {x + 1, y + 1});
        }
        surrounding_positions.push_back(std::pair<int, int> {x + 1, y});
    }
    if (y != 0) {
        surrounding_positions.push_back(std::pair<int, int> {x, y - 1});
    }
    if (y != width - 1) {
        surrounding_positions.push_back(std::pair<int, int> {x, y + 1});
    }

    return surrounding_positions;
}
int GameLogic::Board::count_surrounding_flags(int x, int y) {
    const std::vector<std::pair<int, int>> surrounding_positions = get_surrounding_positions(x, y);
    int count = 0;
    for (auto pos: surrounding_positions) {
        if (visible_map[pos.first][pos.second] == Cover::Flagged) {
            count++;
        }
    }
    return count;
}
void GameLogic::Board::uncover_surroundings(int x, int y) {
    if (map[x][y] == 0) {
        
    }
}
bool GameLogic::Board::select(int x, int y) {
    switch(visible_map[x][y]) {
        case Cover::Covered:
            visible_map[x][y] = Cover::Uncovered;
            if (map[x][y] == 0) {
                uncover_surroundings(x, y);
            }
            return map[x][y] == -1;
        case Cover::Uncovered:
            if (count_surrounding_flags(x, y) == map[x][y]) {
                uncover_surroundings(x, y);
            }
        case Cover::Flagged:
            break;
    }
    return false;
}
bool GameLogic::Board::flag(int x, int y) {
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
    if (map[x][y] == -1) {
        correct_flags++;
    }
    return correct_flags == mine_count;
}