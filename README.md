# C++ TUI Minesweeper
### A TUI (FTXUI) Minesweeper program made with C++

Developed on Ubuntu

This project is a largely pedagogical project for me to practice C++ programming, project design, and test-driven development.

The bash script `project_build.sh` is used for building the project with CMake.
Please note that currently, only GCC and Linux systems are supported.

Subdirectory explanations:
- app - holds the main file that will become the target executable
- tests - holds tests for the library created from src
- src - holds source code of library used by the app
    - core - contains the main interface for the app, and interfaces between the UI and logic
    - ui - code for FTXUI UI components
    - game - game logic code
