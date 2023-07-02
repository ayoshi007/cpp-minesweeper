#include <doctest/doctest.h>
#include <game/controller.hpp>
#include <game/board.hpp>
#include "helper.hpp"

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
    int BoardController::get_value(int x, int y) {
        if (board.get_visible_map()[x][y] != Board::Cover::Uncovered) {
            throw "Location is not uncovered";
        }
        return board.get_map()[x][y];
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
        if (board.is_game_done()) {
            throw "Game is finished";
        }
        return board.get_most_recent_changes();
    }

    const std::vector<std::vector<std::string>> BoardController::get_state_map() {
        return board.get_state_map();
    }
    const std::vector<std::vector<int>>& BoardController::get_map() {
        return board.get_map();
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
    TEST_CASE("Selecting/flagging") {
        GameLogic::BoardController controller;
        controller.initialize_board(5, 5, 5, 5);
        MESSAGE("Displaying board");
        print_map(controller.get_map());
        SUBCASE("Bad select") {
            CHECK_THROWS(controller.select(-1, -1));
        }
        SUBCASE("Bad flag") {
            CHECK_THROWS(controller.flag(-1, -1));
        }
        SUBCASE("Selecting after loss") {
            controller.select(0, 1);
            bool gameOver = controller.select(2, 0);
            CHECK(gameOver == true);
            CHECK_THROWS(controller.select(0, 0));
        }
        SUBCASE("Flagging after loss") {
            controller.select(0, 1);
            controller.select(2, 0);
            CHECK_THROWS(controller.flag(0, 0));
        }
        SUBCASE("Incorrect flag counts") {
            controller.select(0, 1);
            controller.flag(0, 0);
            controller.select(2, 0);
            std::unordered_set<int> incorrect_flags = controller.get_incorrect_flags();
            CHECK(incorrect_flags.size() == 1);
            CHECK(incorrect_flags.find(0) != incorrect_flags.end());
        }
    }
    TEST_CASE("Getting location") {
        GameLogic::BoardController controller;
        controller.initialize_board(5, 5, 5, 5);
        SUBCASE("Getting an uncovered value") {
            controller.select(0, 0);
            CHECK(controller.get_value(0, 0) == 1);
        }
        SUBCASE("Getting a non-uncovered value") {
            CHECK_THROWS(controller.get_value(0, 0));
        }
        SUBCASE("Getting changes after a successful select") {
            controller.select(4, 0);
            const std::vector<std::tuple<int, int, int>> changes = controller.get_changes();
            for (auto change: changes) {
                CHECK_NOTHROW(controller.get_value(std::get<0>(change), std::get<1>(change)));
            }
        }
    }
    TEST_CASE("Winning game") {
        GameLogic::BoardController controller;
        controller.initialize_board(5, 5, 5, 5);
        MESSAGE("Displaying board");
        print_map(controller.get_map());
        CHECK_THROWS(controller.get_incorrect_flags());
        CHECK_THROWS(controller.get_mine_locations());
        CHECK_NOTHROW(controller.get_changes());
        controller.flag(0, 1);
        controller.flag(1, 4);
        controller.flag(2, 0);
        controller.flag(2, 2);
        controller.flag(3, 4);
        CHECK_THROWS(controller.get_incorrect_flags());
        CHECK_THROWS(controller.get_mine_locations());
        CHECK_THROWS(controller.select(0, 0));
        CHECK_THROWS(controller.flag(0, 0));
        CHECK_THROWS(controller.get_changes());
    }
    TEST_CASE("Losing game") {
        GameLogic::BoardController controller;
        controller.initialize_board(5, 5, 5, 5);
        MESSAGE("Displaying board");
        print_map(controller.get_map());
        CHECK_THROWS(controller.get_incorrect_flags());
        CHECK_THROWS(controller.get_mine_locations());
        CHECK_NOTHROW(controller.get_changes());
        controller.select(0, 1);
        controller.select(1, 4);
        CHECK_NOTHROW(controller.get_incorrect_flags());
        CHECK_NOTHROW(controller.get_mine_locations());
        CHECK_THROWS(controller.select(0, 0));
        CHECK_THROWS(controller.flag(0, 0));
        CHECK_THROWS(controller.get_changes());
    }
}