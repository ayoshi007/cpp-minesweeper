#ifndef DRIVER_HPP
#define DRIVER_HPP

// called by main.cpp to start the game itself, serves as main game loop
void mainMenu();
// menu to let player pick custom board size and mine percentage
void customBoardMenu();
// calls game.cpp to start game, waits till end, goes back to mainMenu()'s control
void startGame();

#endif // DRIVER_HPP
