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
    std::vector<std::pair<std::pair<int, int>, int>> BoardController::select(int x, int y) {
        if (x < 0 || x >= board.get_height()) {
            throw "Cannot accept negative arguments";
        }
        if (y < 0 || y >= board.get_width()) {
            throw "Cannot accept negative arguments";
        }
        if (board.is_game_done()) {
            throw "Game is over";
        }
        board.select(x, y);
        return {};
    }
    bool BoardController::flag(int x, int y) {
        if (x < 0 || x >= board.get_height()) {
            throw "Cannot accept negative arguments";
        }
        if (y < 0 || y >= board.get_width()) {
            throw "Cannot accept negative arguments";
        }
        if (board.is_game_done()) {
            throw "Game is over";
        }
        return board.flag(x, y);
    }
    int BoardController::get_flag_count()  {
        return board.get_flag_count();
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