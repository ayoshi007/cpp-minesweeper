# C++ TUI Minesweeper
### A TUI Minesweeper program  
This project is a largely pedagogical project for me to practice C++ programming, project design, and test-driven development.
### Libraries used:  
- [FTXUI](https://github.com/ArthurSonzogni/FTXUI)
- [doctest](https://github.com/doctest/doctest)
### Building and Running
The bash script `project_build.sh` is used for building the project with CMake.  
**Note: only GCC and Linux systems are supported at this time**

The script has the following options:
- `-g` - the build generator to use (default is Ninja)
- `-c` - the CMake build configuration (default is Build)
- `-t` - builds doctest tests (on for Build, off for Release)
- `-nt` - disables tests
- `-ui` - builds interactive UI tests
- `-h` - displays help menu

Make sure your desired build generator is installed.

After building, the executable will be located inside:  
`<project root>/build/<config>_<generator>/app`
