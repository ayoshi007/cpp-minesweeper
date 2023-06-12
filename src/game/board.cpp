#include <core/constants.hpp>

#include <iostream>
#include <unordered_map>
#include <string>
#include <numeric>
#include <algorithm>
#include <random>
#include <game/board.hpp>

GameLogic::Board::Board() = default;
GameLogic::Board::Board(int mt_seed) : Board{constants::DEFAULT_CUSTOM_W, constants::DEFAULT_CUSTOM_H, constants::SMALL_BOARD_MINES, mt_seed} {

}
GameLogic::Board::Board(int w, int h, int mines, int mt_seed) : Board{w, h, mines} {
    g.seed(mt_seed);
}
GameLogic::Board::Board(int w, int h, int mines) :
    correct_flags { 0 },
    lost { false },
    done { false },
    started { false },
    map {},
    visible_map {},
    mine_locations {},
    flag_locations {}
    {
    set_board(w, h, mines);
}
bool GameLogic::Board::is_game_lost() { return lost; }
bool GameLogic::Board::is_game_done() { return done; }
bool GameLogic::Board::is_game_started() { return started; }
int GameLogic::Board::get_mine_count() { return mine_count; }
int GameLogic::Board::get_correct_flags() { return correct_flags; }
/**
 * Clears the board's state back to default values
*/
void GameLogic::Board::clear_board() {
    correct_flags = 0;
    width = 0;
    height = 0;
    mine_count = 0;
    lost = false;
    done = false;
    started = false;
    map.clear();
    visible_map.clear();
    mine_locations.clear();
    flag_locations.clear();
}
/**
 * Sets the board to a new one of the specified width, height, and mine count
 * Input:
 * w - board's new width
 * h - board's new height
 * mines - board's new mine count
*/
void GameLogic::Board::set_board(int w, int h, int mines) {
    clear_board();
    width = w;
    height = h;
    mine_count = mines;
    for (int r{}; r < h; r++) {
        map.push_back(std::vector<int> (w));
        visible_map.push_back(std::vector<Cover> (w));
    }
    std::vector<int> positions (w * h);
    
    // randomly choose the mine locations
    std::iota(positions.begin(), positions.end(), 0);
    std::shuffle(positions.begin(), positions.end(), g);
    for (int i{}; i < mines; i++) {
        int mine_pos = positions[i];
        int r = mine_pos / w;
        int c = mine_pos % w;
        // mines are given a value of -1
        map[r][c] = -1;
        visible_map[r][c] = Cover::Covered;
        mine_locations.insert(i);
        // increments the values of all positions surrounding the mine
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
/**
 * Output
 * - a vector of vector of strings describing the board visible to the player
 *  Contains:
 *  '#' for a flagged cell
 *  '_' for a covered cell
 *  or the underlying value for an uncovered cell
*/
const std::vector<std::vector<std::string>> GameLogic::Board::get_state_map() {
    std::vector<std::vector<std::string>> map_state;
    for (int r = 0; r < height; r++) {
        std::vector<std::string> row_state;
        for (int c = 0; c < width; c++) {
            if (visible_map[r][c] == Cover::Flagged) {
                row_state.push_back("#");
            } else if (visible_map[r][c] == Cover::Covered) {
                row_state.push_back("_");
            } else {
                row_state.push_back(std::to_string(map[r][c]));
            }
        }
        map_state.push_back(row_state);
    }
    return map_state;
}
const std::unordered_set<int>& GameLogic::Board::get_mine_locations() {
    return mine_locations;
}
/**
 * Input:
 *  x - the row of the cell
 *  y - the column of a cell
 * 
 * Output:
 *  a vector of coordinate pairs of all cells surrounding x and y
*/
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
/**
 * Input:
 *  surrounding_positions - a vector of coordinate pairs
 * Output:
 *  An unordered map mapping each Cover to a number corresponding to the number of each Cover type in the
 *      input vector
*/
std::unordered_map<GameLogic::Board::Cover, int> GameLogic::Board::get_visibilities(const std::vector<std::pair<int, int>>& surrounding_positions) {
    std::unordered_map<GameLogic::Board::Cover, int> counts;
    counts[Cover::Covered] = 0;
    counts[Cover::Uncovered] = 0;
    counts[Cover::Flagged] = 0;
    for (auto pos: surrounding_positions) {
        counts[visible_map[pos.first][pos.second]]++;
    }
    return counts;
}
/**
 * A helper function used by select()
 * Will recursively uncover the visible map according to what value is at row x, column y
 * Input:
 *  x - the row to uncover
 *  y - the column to uncover
 * Output
 *  A boolean indicating whether or not a mine was uncovered
*/
bool GameLogic::Board::uncover_surroundings(int x, int y) {
    // static int count = 0;
    // count++;
    // if (count > 100) {
    //     std::exit(1);
    // }

    // mines are uncovered and stop uncovering (returns true)
    if (map[x][y] == -1) {
        visible_map[x][y] = Cover::Uncovered;
        return true;
    }
    bool mine_detonated = false;
    const std::vector<std::pair<int, int>> surrounding_positions = get_surrounding_positions(x, y);

    // uncover Covered cells
    if (visible_map[x][y] == Cover::Covered) {
        visible_map[x][y] = Cover::Uncovered;
        // cells with a value greater than 0 only uncover themselves
        if (map[x][y] != 0) {
            //std::cout << "Uncovering r = " << x << ", c = " << y << '\n';
            visible_map[x][y] = Cover::Uncovered;
        }
        // cells with a value 0 will uncover their surroundings recursively
        else {
            //std::cout << "Uncovering all around r = " << x << ", c = " << y << '\n';
            visible_map[x][y] == Cover::Uncovered;
            for (auto pos: surrounding_positions) {
                // recursive call
                mine_detonated |= select(pos.first, pos.second);
            }
        }
    }
    // Uncovered cells that have a value greater than 0 may be used to uncover surroundings
    else if (map[x][y] != 0) {
        //std::cout << "Checking flags around r = " << x << ", c = " << y << '\n';

        // if the cell's value equals the number of surrounding cells that are flagged, and
        //  there are uncovered cells surrounding the cell, then uncover the surrounding cells recursively
        std::unordered_map<Cover, int> visibilties = get_visibilities(surrounding_positions);
        if (visibilties[Cover::Covered] > 0 && visibilties[Cover::Flagged] == map[x][y]) {
            //std::cout << "Uncovering around r = " << x << ", c = " << y << '\n';
            for (auto pos: surrounding_positions) {
                mine_detonated |= select(pos.first, pos.second);
            }
        }
    }
    // return whether or not recursive calls uncovered a mine
    return mine_detonated;
}
/**
 * Randomly finds an uncovered cell's coordinates given a mine's location
 * Input:
 *  x - the row of a mine
 *  y - the column of a mine
 * Output:
 *  the coordinates of an un-mined cell
*/
std::pair<int, int> GameLogic::Board::find_free_pos(int x, int y) {
    // creates a random sequence of positions from which to choose from
    std::vector<int> positions (width * height);
    std::iota(positions.begin(), positions.end(), 0);
    std::shuffle(positions.begin(), positions.end(), g);
    int i{};
    // returns the first free spot
    while (mine_locations.find(positions[i]) != mine_locations.end()) {
        i++;
    }
    std::pair<int, int> free_pos {positions[i] / width, positions[i] % width};
    return free_pos;
}
/**
 * Selects the cell at row x, column y.
 * Will guarantee that the first selected cell in the board does not cause a game over.
 * Returns whether or not the select move caused a mine to detonate.
 * Input:
 *  x - the row to select
 *  y - the column to select
 * Output:
 *  a boolean describing whether or not a mine was detonated
*/
bool GameLogic::Board::select(int x, int y) {
    // if this call to select() is a first move, make sure it doesn't cause a game over
    if (!started) {
        started = true;
        // if the first selected position is a mine position, swap it with a free position and then proceed with the rest of the function
        if (map[x][y] == -1) {
            // find a free position, and the surrounding positions of the selected and free position
            std::pair<int, int> free_pos = find_free_pos(x, y);
            std::vector<std::pair<int, int>> old_spot_surroundings = get_surrounding_positions(x, y);
            std::vector<std::pair<int, int>> new_spot_surroundings = get_surrounding_positions(free_pos.first, free_pos.second);

            // make the selected position a free position
            map[x][y] = 0;
            mine_locations.erase(x * width + y);
            for (auto pos: old_spot_surroundings) {
                if (map[pos.first][pos.second] == -1) {
                    map[x][y]++;
                } else {
                    map[pos.first][pos.second] = std::max(map[pos.first][pos.second] - 1, 0);
                }
            }
            // make the free position a mine location
            map[free_pos.first][free_pos.second] = -1;
            mine_locations.insert(free_pos.first * width + free_pos.second);
            for (auto pos: new_spot_surroundings) {
                map[pos.first][pos.second] = map[pos.first][pos.second] == -1 ? map[pos.first][pos.second] : map[pos.first][pos.second] + 1;
            }
        }
    }
    // allow selection for covered and uncovered locations
    // flagged locations cannot be selected
    switch(visible_map[x][y]) {
        case Cover::Covered:
        case Cover::Uncovered:
            lost = uncover_surroundings(x, y);
        case Cover::Flagged:
            break;
    }
    // returns whether or not a mine was detonated
    done |= lost;
    return lost;
}
/**
 * Flags the location at row x, column y
 * Input:
 *  x - row of location to flag
 *  y - column of location to flag
 * Output:
 *  whether or not the number of correct flags are equal to the mine count
 *      (i.e. if the game has been won)
*/
bool GameLogic::Board::flag(int x, int y) {
    switch (visible_map[x][y]) {
        // covered locations may be flagged
        case Cover::Covered:
            visible_map[x][y] = Cover::Flagged;
            if (map[x][y] == -1) {
                correct_flags++;
            }
            break;
        case Cover::Uncovered:
            break;
        // flagged locations may be unflagged
        case Cover::Flagged:
            visible_map[x][y] = Cover::Covered;
            if (map[x][y] == -1) {
                correct_flags--;
            }
            break;
    }
    done = correct_flags == mine_count;
    return done;
}