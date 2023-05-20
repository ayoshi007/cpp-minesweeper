#ifndef BOARD_HPP
#define BOARD_HPP

int usingFTXUI();

class Board {
    private:
        const int width;
        const int height;
        const int mines;
        int flagged{};
    public:
        Board(int w, int h, int mines);
        int getWidth() { return width; }
        int getHeight() { return height; }
        int getMines() { return mines; }
        int getFlagged() { return flagged; }
        void clearBoard();
        void initBoard();
        bool select(int i, int j);
};

/*
Make 2 child classes:
- static board
    - uses a statically created int array for the board (instead of having to dyn. allocate a board of known size)
- custom board
    - uses a dynamically allocated int array for the board

- both need to support the same functions, just with different array types for the board
*/
class StaticBoard {

};

class CustomBoard {

};

#endif // BOARD_HPP