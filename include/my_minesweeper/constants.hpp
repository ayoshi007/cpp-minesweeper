#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

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
    extern const int DEFAULT_CUSTOM_MINES {90};

    extern int smallBoard[SMALL_BOARD_H][SMALL_BOARD_W] {};
    extern int medBoard[MED_BOARD_H][MED_BOARD_W] {};
    extern int largeBoard[LARGE_BOARD_H][LARGE_BOARD_W] {};
}

#endif // CONSTANTS_HPP