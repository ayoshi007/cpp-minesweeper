#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

namespace constants {
    extern const int SMALL_BOARD_W;
    extern const int SMALL_BOARD_H;
    extern const int SMALL_BOARD_MINES;
    extern const int MED_BOARD_W;
    extern const int MED_BOARD_H;
    extern const int MED_BOARD_MINES;
    extern const int LARGE_BOARD_W;
    extern const int LARGE_BOARD_H;
    extern const int LARGE_BOARD_MINES;
    extern const int DEFAULT_CUSTOM_W;
    extern const int DEFAULT_CUSTOM_H;
    extern const int DEFAULT_CUSTOM_PERCENT;

    extern const int MAIN_MENU_SCREEN;
    extern const int GAME_BOARD_SCREEN;

    extern const std::string SMALL_BOARD_BUTTON_LABEL;
    extern const std::string MED_BOARD_BUTTON_LABEL;
    extern const std::string LARGE_BOARD_BUTTON_LABEL;
    extern const std::string CUSTOM_BOARD_BUTTON_LABEL;
    /*
    extern int smallBoard[SMALL_BOARD_H][SMALL_BOARD_W];
    extern int medBoard[MED_BOARD_H][MED_BOARD_W];
    extern int largeBoard[LARGE_BOARD_H][LARGE_BOARD_W];
    */
}

#endif // CONSTANTS_HPP