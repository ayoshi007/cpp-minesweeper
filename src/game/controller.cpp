#include <doctest/doctest.h>
#include <game/controller.hpp>
#include <game/board.hpp>

namespace GameLogic {
    BoardController::BoardController() {
    }
    bool BoardController::initialize_board(int width, int height, int mine_count, int seed) {
        if (width <= 0 || height <= 0 || mine_count <= 0) {
            throw "Cannot accept negative arguments";
        }
        if (width * height <= mine_count) {
            throw "Mine count cannot exceed total number of cells";
        }
        board = Board(width, height, mine_count, seed);
        return true;
    }
    bool BoardController::initialize_board(int width, int height, int mine_count) {
        if (width <= 0 || height <= 0 || mine_count <= 0) {
            throw "Cannot accept negative arguments";
        }
        if (width * height <= mine_count) {
            throw "Mine count cannot exceed total number of cells";
        }
        board = Board(width, height, mine_count);
        return true;
    }
    bool BoardController::select(int x, int y) {
        if (x < 0 || x >= board.get_height() || y < 0 || y >= board.get_width()) {
            throw "Bad x, y arguments";
        }
        if (board.is_game_done()) {
            throw "Game is finished";
        }
        return board.select(x, y);
    }
    bool BoardController::flag(int x, int y) {
        if (x < 0 || x >= board.get_height() || y < 0 || y >= board.get_width()) {
            throw "Bad x, y arguments";
        }
        if (board.is_game_done()) {
            throw "Game is finished";
        }
        return board.flag(x, y);
    }
    int BoardController::get_flag_count()  {
        return board.get_flag_count();
    }
    const std::unordered_set<int>& BoardController::get_mine_locations() {
        if (!board.is_game_lost()) {
            throw "Game is not lost";
        }
        return board.get_mine_locations();
    }
    std::unordered_set<int> BoardController::get_incorrect_flags() {
        if (!board.is_game_lost()) {
            throw "Game is not lost";
        }
        std::unordered_set<int> incorrect_flags;
        for (int flag: board.get_flag_locations()) {
            if (board.get_mine_locations().find(flag) == board.get_mine_locations().end()) {
                incorrect_flags.insert(flag);
            }
        }
        return incorrect_flags;
    }
    const std::vector<std::tuple<int, int, int>>& BoardController::get_changes() {
        if (board.is_game_lost()) {
            throw "Game has been lost";
        }
        return board.get_most_recent_changes();
    }
}

TEST_SUITE("Board controller") {
    TEST_CASE("Board controller creation") {
        SUBCASE("Create controller") {
            GameLogic::BoardController controller;
            MESSAGE("Created controller");
        }
        SUBCASE("Create controller and initialize board") {
            GameLogic::BoardController controller;
            controller.initialize_board(8, 8, 10, 5);
            MESSAGE("Created controller and initialized board with seed");
        }
        SUBCASE("Check erroneous initialize board arguments") {
            GameLogic::BoardController controller;
            SUBCASE("Negative args")  {
                CHECK_THROWS(controller.initialize_board(-8, 8, 10));
            }
            SUBCASE("Too many mines") {
                CHECK_THROWS(controller.initialize_board(8, 8, 64));
            }
        }
    }
}