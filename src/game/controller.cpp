#include <game/controller.hpp>
#include <game/board.hpp>

namespace GameLogic {
    BoardController::BoardController() : board {} {

    }
    bool BoardController::initialize_board(int width, int height, int mine_count, int seed) {
        
    }
    bool BoardController::initialize_board(int width, int height, int mine_count) {
        if (width <= 0 || height <= 0 || mine_count <= 0) {
            throw "Cannot accept negative arguments";
        }
        if (width * height <= mine_count) {
            throw "Mine count cannot exceed total number of cells";
        }
        board.set_board(width, height, mine_count);
        return true;
    }
    bool BoardController::select(int x, int y) {
        if (x < 0 || x >= board.get_height()) {
            throw "Cannot accept negative arguments";
        }
        if (y < 0 || y >= board.get_width()) {
            throw "Cannot accept negative arguments";
        }
        return board.select(x, y);
    }
    bool BoardController::flag(int x, int y) {
        if (x < 0 || x >= board.get_height()) {
            throw "Cannot accept negative arguments";
        }
        if (y < 0 || y >= board.get_width()) {
            throw "Cannot accept negative arguments";
        }
        return board.flag(x, y);
    }
    int BoardController::get_flag_count()  {
        return board.get_flag_count();
    }
}