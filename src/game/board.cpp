#include <doctest/doctest.h>
#include <core/constants.hpp>
#include "helper.hpp"

#include <iostream>
#include <unordered_map>
#include <tuple>
#include <string>
#include <numeric>
#include <algorithm>
#include <random>
#include <game/board.hpp>

namespace GameLogic {
    Board::Board() = default;
    Board::Board(int mt_seed) : Board{constants::DEFAULT_CUSTOM_W, constants::DEFAULT_CUSTOM_H, constants::SMALL_BOARD_MINES, mt_seed} {

    }
    Board::Board(int w, int h, int mines, int mt_seed) : Board{w, h, mines} 
        {
        g.seed(mt_seed);
    }
    Board::Board(int w, int h, int mines) :
        flag_count { 0 }, 
        correct_flag_count { 0 },
        lost { false },
        done { false },
        started { false },
        map {},
        visible_map {},
        mine_locations {},
        flag_locations {},
        most_recent_changes {}
        {
    }
    int Board::get_width() { return width; }
    int Board::get_height() { return height; }
    bool Board::is_game_lost() { return lost; }
    bool Board::is_game_done() { return done; }
    bool Board::is_game_started() { return started; }
    int Board::get_flag_count() { return flag_count; }
    int Board::get_mine_count() { return mine_count; }
    int Board::get_correct_flag_count() { return correct_flag_count; }
    /**
     * Clears the board's state back to default values
    */
    void Board::reset_game() {
        flag_count = 0;
        correct_flag_count = 0;
        lost = false;
        done = false;
        started = false;
        flag_locations.clear();
        most_recent_changes.clear();
        for (int r = 0; r < visible_map.size(); r++) {
            for (int c = 0; c < visible_map[r].size(); c++) {
                visible_map[r][c] = Cover::Covered;
            }
        }
    }
    
    const std::vector<std::vector<int>>& Board::get_map() {
        return map;
    }
    const std::vector<std::vector<Board::Cover>>& Board::get_visible_map() {
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
    const std::vector<std::vector<std::string>> Board::get_state_map() {
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
    const std::unordered_set<int>& Board::get_mine_locations() {
        return mine_locations;
    }
    const std::unordered_set<int>& Board::get_flag_locations() {
        return flag_locations;
    }
    const std::vector<std::tuple<int, int, int>>& Board::get_most_recent_changes() {
        return most_recent_changes;
    }
    /**
     * Input:
     *  x - the row of the cell
     *  y - the column of a cell
     * 
     * Output:
     *  a vector of coordinate pairs of all cells surrounding x and y
    */
    const std::vector<std::pair<int, int>> Board::get_surrounding_positions(int r, int c) {
        std::vector<std::pair<int, int>> surrounding_positions;
        
        if (r != 0) {
            if (c != 0) {
                surrounding_positions.push_back(std::pair<int, int> {r - 1, c - 1});
            }
            if (c != width - 1) {
                surrounding_positions.push_back(std::pair<int, int> {r - 1, c + 1});
            }
            surrounding_positions.push_back(std::pair<int, int> {r - 1, c});
        }
        if (r != height - 1) {
            if (c != 0) {
                surrounding_positions.push_back(std::pair<int, int> {r + 1, c - 1});
            }
            if (c != width - 1) {
                surrounding_positions.push_back(std::pair<int, int> {r + 1, c + 1});
            }
            surrounding_positions.push_back(std::pair<int, int> {r + 1, c});
        }
        if (c != 0) {
            surrounding_positions.push_back(std::pair<int, int> {r, c - 1});
        }
        if (c != width - 1) {
            surrounding_positions.push_back(std::pair<int, int> {r, c + 1});
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
    std::unordered_map<Board::Cover, int> Board::get_visibilities(const std::vector<std::pair<int, int>>& surrounding_positions) {
        std::unordered_map<Board::Cover, int> counts;
        counts[Cover::Covered] = 0;
        counts[Cover::Uncovered] = 0;
        counts[Cover::Flagged] = 0;
        for (auto pos: surrounding_positions) {
            counts[visible_map[pos.first][pos.second]]++;
        }
        return counts;
    }
    /**
     * Sets the board's mine locations, avoiding the given position and it's 
     *  adjacent positions.
     * Input:
     * first_r - the row of the position to avoid
     * first_c - the column of the position to avoid
    */
    void Board::set_board(int first_r, int first_c) {
        clear_board();
        std::vector<std::pair<int, int>> mine_free_positions = get_surrounding_positions(first_r, first_c);
        mine_free_positions.push_back({first_r, first_c});
        for (int r{}; r < height; r++) {
            map.push_back(std::vector<int> (width));
            visible_map.push_back(std::vector<Cover> (width));
        }
        std::vector<int> positions (width * height);
        
        // randomly choose the mine locations
        std::iota(positions.begin(), positions.end(), 0);
        std::shuffle(positions.begin(), positions.end(), g);
        for (int i{}; i < mines; i++) {
            int mine_pos = positions[i];
            int r = mine_pos / w;
            int c = mine_pos % w;
            visible_map[r][c] = Cover::Covered;
            if (std::find(mine_free_positions.begin(), mine_free_positions.end(), {r, c}) != mine_free_positions.end()) {
                continue;
            }
            // mines are given a value of -1
            map[r][c] = -1;
            mine_locations.insert(mine_pos);
            // increments the values of all positions surrounding the mine
            const std::vector<std::pair<int, int>> surrounding_positions = get_surrounding_positions(r, c);
            for (auto pos: surrounding_positions) {
                map[pos.first][pos.second] = map[pos.first][pos.second] == -1 ? map[pos.first][pos.second] : map[pos.first][pos.second] + 1;
            }
        }
    }
    /**
     * Selects the cell at row x, column y.
     * Will guarantee that the first selected cell in the board does not cause a game over.
     * Returns whether or not the select_helper move caused a mine to detonate.
     * Input:
     *  x - the row to select
     *  y - the column to select
     * Output:
     *  a boolean describing whether or not a mine was detonated
    */
    bool Board::select_helper(int r, int c) {
        // allow selection for covered and uncovered locations
        // flagged locations cannot be selected
        switch(visible_map[r][c]) {
            case Cover::Covered:
            case Cover::Uncovered:
                lost = uncover_surroundings(r, c);
                break;
            default:
                break;
            
        }
        // returns whether or not a mine was detonated
        done |= lost;
        return lost;
    }
    /**
     * A helper function used by select_helper()
     * Will recursively uncover the visible map according to what value is at row x, column y
     * Input:
     *  x - the row to uncover
     *  y - the column to uncover
     * Output
     *  A boolean indicating whether or not a mine was uncovered
    */
    bool Board::uncover_surroundings(int r, int c) {
        // mines are uncovered and stop uncovering (returns true)
        if (map[r][c] == -1) {
            most_recent_changes.push_back({r, c, -1});
            visible_map[r][c] = Cover::Uncovered;
            return true;
        }
        bool mine_detonated = false;
        const std::vector<std::pair<int, int>> surrounding_positions = get_surrounding_positions(r, c);

        // uncover Covered cells
        if (visible_map[r][c] == Cover::Covered) {
            most_recent_changes.push_back({r, c, map[r][c]});
            visible_map[r][c] = Cover::Uncovered;
            // cells with a value 0 will uncover their surroundings recursively
            // note that cells with a value greater than 0 will only uncover themselves
            if (map[r][c] == 0) {
                for (auto pos: surrounding_positions) {
                    // recursive call
                    mine_detonated |= select_helper(pos.first, pos.second);
                }
            }
        }
        // Uncovered cells that have a value greater than 0 may be used to uncover surroundings
        else if (map[r][c] != 0) {
            // if the cell's value equals the number of surrounding cells that are flagged, and
            //  there are uncovered cells surrounding the cell, then uncover the surrounding cells recursively
            std::unordered_map<Cover, int> visibilties = get_visibilities(surrounding_positions);
            if (visibilties[Cover::Covered] > 0 && visibilties[Cover::Flagged] == map[r][c]) {
                for (auto pos: surrounding_positions) {
                    // need to change this to only uncover surroundings recursively if the value is 0
                    mine_detonated |= select_helper(pos.first, pos.second);
                }
            }
        }
        // return whether or not recursive calls uncovered a mine
        return mine_detonated;
    }
    
    bool Board::select(int r, int c) {
        // on the first move, initialize the board
        // the first selected position is guaranteed to be a 0
        if (!started) {
            started = true;
            set_board(r, c);
        }
        most_recent_changes.clear();
        return select_helper(r, c);
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
    bool Board::flag(int r, int c) {
        switch (visible_map[r][c]) {
            // covered locations may be flagged
            case Cover::Covered:
                visible_map[r][c] = Cover::Flagged;
                flag_count++;
                flag_locations.insert(r * width + c);
                if (map[r][c] == -1) {
                    correct_flag_count++;
                }
                break;
            case Cover::Uncovered:
                break;
            // flagged locations may be unflagged
            case Cover::Flagged:
                visible_map[r][c] = Cover::Covered;
                flag_count--;
                flag_locations.erase(r * width + c);
                if (map[r][c] == -1) {
                    correct_flag_count--;
                }
                break;
            default:
                break;
        }
        done = correct_flag_count == mine_count;
        return done;
    }
}

TEST_SUITE("Board object") {
    TEST_CASE("Board object creation") {
        GameLogic::Board b {5, 5, 10};
        CHECK(b.get_width() == 5);
        CHECK(b.get_height() == 5);
        CHECK(b.get_mine_count() == 10);
    }
    TEST_CASE("Flagging") {
        GameLogic::Board b {8, 8, 10, 5};
        SUBCASE("Flag uncovered position") {
            b.select(0, 0);
            b.flag(0, 0);
            CHECK(b.get_visible_map()[0][0] == GameLogic::Board::Cover::Uncovered);
            CHECK(b.get_flag_count() == 0);
            CHECK(b.get_flag_locations().size() == 0);
        }
        SUBCASE("Flag covered position") {
            b.flag(0, 0);
            CHECK(b.get_visible_map()[0][0] == GameLogic::Board::Cover::Flagged);
            CHECK(b.get_flag_count() == 1);
            CHECK(b.get_flag_locations().size() == 1);
        }
        SUBCASE("Flag flagged position") {
            b.flag(0, 0);
            b.flag(0, 0);
            CHECK(b.get_visible_map()[0][0] == GameLogic::Board::Cover::Covered);
            CHECK(b.get_flag_count() == 0);
            CHECK(b.get_flag_locations().size() == 0);
        }
        SUBCASE("Flag all mines") {
            bool allFlagged = false;
            for (int loc: b.get_mine_locations()) {
                allFlagged = b.flag(loc / b.get_width(), loc % b.get_width());
            }
            CHECK(allFlagged == true);
            CHECK(b.get_correct_flag_count() == b.get_mine_count());
            CHECK(b.get_flag_locations().size() == b.get_correct_flag_count());
            CHECK(b.get_flag_locations().size() == b.get_mine_count());
            if (!allFlagged) {
                MESSAGE("Displaying board and player board");
                print_map(b.get_map());
                print_map(b.get_state_map());
            }
        }
    }
    
    TEST_CASE("Selecting") {
        GameLogic::Board b {8, 8, 10, 5};
        /*
        MESSAGE("Displaying map");
        print_map(b.get_map());
        */
        SUBCASE("First select mine location") {
            bool gameOver = b.select(1, 2);
            CHECK(gameOver == false);
            CHECK(b.is_game_lost() == false);
            CHECK(b.is_game_done() == false);
            if (gameOver) {
                MESSAGE("Displaying visible board");
                print_map(b.get_state_map());
            }
        }
        SUBCASE("Non mine location") {
            bool gameOver = b.select(0, 4);
            CHECK(gameOver == false);
            CHECK(b.is_game_lost() == false);
            CHECK(b.is_game_done() == false);
            if (gameOver) {
                MESSAGE("Displaying visible board");
                print_map(b.get_state_map());
            }
            CHECK(b.get_most_recent_changes().size() == 1);
        }
        SUBCASE("Mine location after first select") {
            b.select(0, 4);
            bool gameOver = b.select(1, 2);
            CHECK(gameOver == true);
            CHECK(b.is_game_lost() == true);
            CHECK(b.is_game_done() == true);
            if (!gameOver) {
                MESSAGE("Displaying visible board");
                print_map(b.get_state_map());
            }
        }
        SUBCASE("Select position with 0 mines around it") {
            b.select(0, 5);
            CHECK(b.get_most_recent_changes().size() == 18);
            const std::vector<std::tuple<int, int, int>> changes = b.get_most_recent_changes();
            for (auto change: changes) {
                CHECK(b.get_visible_map()[std::get<0>(change)][std::get<1>(change)] == GameLogic::Board::Cover::Uncovered);
                CHECK(b.get_map()[std::get<0>(change)][std::get<1>(change)] == std::get<2>(change));
            }
        }
        SUBCASE("Select uncovered position with equal number of flags around it") {
            b.select(0, 0);
            b.flag(0, 1);
            b.select(0, 0);
            CHECK(b.get_visible_map()[1][0] == GameLogic::Board::Cover::Uncovered);
            CHECK(b.get_visible_map()[1][1] == GameLogic::Board::Cover::Uncovered);
            CHECK(b.get_correct_flag_count() == 1);
            CHECK(b.get_most_recent_changes().size() == 2);
        }
        SUBCASE("Select uncovered position without equal number of flags around it") {
            b.select(0, 0);
            b.select(0, 0);
            CHECK(b.get_visible_map()[0][1] == GameLogic::Board::Cover::Covered);
            CHECK(b.get_visible_map()[1][0] == GameLogic::Board::Cover::Covered);
            CHECK(b.get_visible_map()[1][1] == GameLogic::Board::Cover::Covered);
            CHECK(b.get_most_recent_changes().empty());
        }
        SUBCASE("Select uncovered position with equal number of flags at incorrect positions") {
            b.select(0, 0);
            b.flag(1, 0);
            bool gameOver = b.select(0, 0);
            CHECK(gameOver == true);
            CHECK(b.get_most_recent_changes().size() == 2);
            CHECK(b.is_game_lost() == true);
            CHECK(b.is_game_done() == true);
        }
    }
}