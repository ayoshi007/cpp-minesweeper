#include <my_minesweeper/constants.hpp>
#include <my_minesweeper/board.hpp>

/*
Handle state of game (includes board, screen, as well as time)
Receives control from driver to be the 'controller' of the game
Handle user input of FTXUI components
Control effect of input on board state and screen state
Handle game over/win, returns control back to driver
*/