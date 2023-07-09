#include <core/constants.hpp>

namespace constants {
    extern const int SMALL_BOARD_W {8};
    extern const int SMALL_BOARD_H {8};
    extern const int SMALL_BOARD_MINES {10};
    extern const int MED_BOARD_W {16};
    extern const int MED_BOARD_H {16};
    extern const int MED_BOARD_MINES {40};
    extern const int LARGE_BOARD_W {30};
    extern const int LARGE_BOARD_H {16};
    extern const int LARGE_BOARD_MINES {99};
    extern const int DEFAULT_CUSTOM_W {30};
    extern const int DEFAULT_CUSTOM_H {30};
    extern const int DEFAULT_CUSTOM_PERCENT {15};

    extern const std::string SMALL_BOARD_BUTTON_LABEL {"Small board (8x8, 10 mines)"};
    extern const std::string MED_BOARD_BUTTON_LABEL {"Medium board (16x16, 40 mines)"};
    extern const std::string LARGE_BOARD_BUTTON_LABEL {"Large board (30x16, 99 mines)"};
    extern const std::string CUSTOM_BOARD_BUTTON_LABEL {"Custom board"};

    extern const std::string MAIN_MENU_SUBTITLE {"Main menu"};
    extern const std::string GAME_BOARD_SUBTITLE {"Flag the mines!"};
    /*
    extern int smallBoard[SMALL_BOARD_H][SMALL_BOARD_W] {};
    extern int medBoard[MED_BOARD_H][MED_BOARD_W] {};
    extern int largeBoard[LARGE_BOARD_H][LARGE_BOARD_W] {};
    */
}