#include <doctest/doctest.h>
#include <game/controller.hpp>
#include <game/board.hpp>
#include "helper.hpp"

namespace GameLogic {
    BoardController::BoardController() : detonated_mine {-1, -1} {
    }
    bool BoardController::initialize_board(int width, int height, int mine_count, int seed) {
        if (width <= 0 || height <= 0 || mine_count <= 0) {
            throw "Cannot accept negative arguments";
        }
        if (width * height - 10 < mine_count) {
            throw "Mine count must leave at least 10 open spaces";
        }
        board = Board(width, height, mine_count, seed);
        return true;
    }
    bool BoardController::initialize_board(int width, int height, int mine_count) {
        if (width <= 0 || height <= 0 || mine_count <= 0) {
            throw "Cannot accept negative arguments";
        }
        if (width * height - 10 < mine_count) {
            throw "Mine count must leave at least 10 open spaces";
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
        bool game_over = board.select(x, y);
        if (game_over) {
            for (auto change: board.get_most_recent_changes()) {
                if (std::get<2>(change) == -1) {
                    detonated_mine = {std::get<0>(change), std::get<1>(change)};
                }
            }
        }
        return game_over;
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
        if (!board.is_game_started() || (!board.is_game_done() && board.get_visible_map()[x][y] != Board::Cover::Uncovered)) {
            throw "Location is not uncovered";
        }
        return board.get_map()[x][y];
    }
    Board::Cover BoardController::get_cover(int x, int y) {
        return board.get_visible_map()[x][y];
    }
    bool BoardController::is_game_lost() { return board.is_game_lost(); }
    bool BoardController::is_game_won() { return board.is_game_done() && !board.is_game_lost(); }
    const std::unordered_set<int>& BoardController::get_mine_locations() {
        if (!board.is_game_lost()) {
            throw "Game is not lost";
        }
        return board.get_mine_locations();
    }
    const std::pair<int, int>& BoardController::get_detonated_mine() {
        if (!board.is_game_lost()) {
            throw "Game is not lost";
        }
        return detonated_mine;
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
                CHECK_THROWS(controller.initialize_board(8, 8, 55));
            }
            SUBCASE("Max possible mines") {
                CHECK_NOTHROW(controller.initialize_board(8, 8, 54));
            }
        }
    }
    TEST_CASE("Selecting/flagging") {
        GameLogic::BoardController controller;
        controller.initialize_board(8, 8, 10, 5);
        MESSAGE("Displaying board");
        print_map(controller.get_map());
        SUBCASE("Bad select") {
            CHECK_THROWS(controller.select(-1, -1));
        }
        SUBCASE("Bad flag") {
            CHECK_THROWS(controller.flag(-1, -1));
        }
        SUBCASE("Selecting after loss") {
            controller.select(0, 0);
            bool gameOver = controller.select(1, 2);
            CHECK(gameOver == true);
            CHECK(controller.get_detonated_mine() == std::pair<int, int> {1, 2});
            CHECK_THROWS(controller.select(0, 0));
        }
        SUBCASE("Flagging after loss") {
            controller.select(0, 0);
            controller.select(1, 2);
            CHECK_THROWS(controller.flag(0, 0));
        }
        SUBCASE("Incorrect flag counts") {
            controller.select(0, 0);
            controller.flag(0, 2);
            controller.select(2, 1);
            std::unordered_set<int> incorrect_flags = controller.get_incorrect_flags();
            CHECK(incorrect_flags.size() == 1);
            CHECK(incorrect_flags.find(2) != incorrect_flags.end());
            CHECK(controller.get_detonated_mine() == std::pair<int, int> {2, 1});
            MESSAGE("Printing visible map");
            print_map(controller.get_state_map());
        }
        SUBCASE("Detonated mine from selecting an incorrected flagged number") {
            controller.select(0, 0);
            controller.flag(0, 2);
            controller.select(0, 1);
            std::unordered_set<int> incorrect_flags = controller.get_incorrect_flags();
            CHECK(controller.get_detonated_mine() == std::pair<int, int> {1, 2});
            MESSAGE("Printing visible map");
            print_map(controller.get_state_map());
        }
    }
    TEST_CASE("Getting location") {
        GameLogic::BoardController controller;
        controller.initialize_board(8, 8, 10, 5);
        SUBCASE("Getting an uncovered value") {
            controller.select(0, 0);
            CHECK(controller.get_value(0, 0) == 0);
            CHECK(controller.get_value(0, 1) == 1);
            CHECK(controller.get_value(1, 0) == 1);
            CHECK(controller.get_value(1, 1) == 2);
        }
        SUBCASE("Attempt at getting a value before start") {
            CHECK_THROWS(controller.get_value(0, 0));
        }
        SUBCASE("Attempt at getting an uncovered value") {
            controller.select(0, 0);
            CHECK_THROWS(controller.get_value(7, 7));
        }
        SUBCASE("Getting changes after a successful select") {
            controller.select(0, 0);
            const std::vector<std::tuple<int, int, int>> changes = controller.get_changes();
            for (auto change: changes) {
                CHECK_NOTHROW(controller.get_value(std::get<0>(change), std::get<1>(change)));
            }
        }
    }
    TEST_CASE("Winning game") {
        GameLogic::BoardController controller;
        controller.initialize_board(8, 8, 10, 5);
        MESSAGE("Displaying board");
        print_map(controller.get_map());
        CHECK_THROWS(controller.get_incorrect_flags());
        CHECK_THROWS(controller.get_mine_locations());
        CHECK_NOTHROW(controller.get_changes());
        controller.flag(1, 2);
        controller.flag(1, 3);
        controller.flag(2, 1);
        controller.flag(3, 5);
        controller.flag(5, 0);
        controller.flag(5, 5);
        controller.flag(6, 4);
        controller.flag(6, 7);
        controller.flag(7, 1);
        controller.flag(7, 2);
        controller.select(0, 0);
        CHECK_THROWS(controller.get_incorrect_flags());
        CHECK_THROWS(controller.get_mine_locations());
        CHECK_THROWS(controller.select(0, 0));
        CHECK_THROWS(controller.flag(0, 0));
        CHECK_THROWS(controller.get_changes());
    }
    TEST_CASE("Losing game") {
        GameLogic::BoardController controller;
        controller.initialize_board(8, 8, 10, 5);
        MESSAGE("Displaying board");
        print_map(controller.get_map());
        CHECK_THROWS(controller.get_incorrect_flags());
        CHECK_THROWS(controller.get_mine_locations());
        CHECK_NOTHROW(controller.get_changes());
        controller.select(0, 0);
        controller.select(1, 2);
        CHECK_NOTHROW(controller.get_incorrect_flags());
        CHECK_NOTHROW(controller.get_mine_locations());
        CHECK_THROWS(controller.select(0, 0));
        CHECK_THROWS(controller.flag(0, 0));
        CHECK_THROWS(controller.get_changes());
    }
}