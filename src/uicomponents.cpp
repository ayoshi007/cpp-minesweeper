/*
Handle FTXUI
Includes UI of:
- game board
- main menu
- custom board menu
- game over/win screen
*/
#include <iostream>
#include <memory>

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/screen/terminal.hpp>

#include <my_minesweeper/uicomponents.hpp>
#include <my_minesweeper/constants.hpp>

using namespace ftxui;

// all variables are declared static to prevent external linkage
namespace GameUI {
    void setWindowBar();
    void setContentMainMenu();
    void setContentBoard(int width, int height, int mineCount);
    void setWindowRenderer();
    void setMainMenu();
    void setBoard(int width, int height, int mineCount);
    void changeMenuSubtitle(const std::string& subtitle);
    void startScreenLoop();

    /* functors and variables */
    static bool quitModalShown = false;
    static bool customBoardModalShown = false;
    static std::string topBarSubtitle {};
    static int boardWidth {constants::DEFAULT_CUSTOM_W};
    static int boardHeight {constants::DEFAULT_CUSTOM_H};
    static int minePercent {constants::DEFAULT_CUSTOM_PERCENT};
    
    static auto showQuitModal = [] { quitModalShown = true; };
    static auto hideQuitModal = [] { quitModalShown = false; };
    static auto showCustomBoardModal = [] { customBoardModalShown = true; };
    static auto hideCustomBoardModal = [] { customBoardModalShown = false; };
    static auto createSmallBoard = [] {
        setBoard(constants::SMALL_BOARD_W, constants::SMALL_BOARD_H, constants::SMALL_BOARD_MINES);
        };
    static auto createMedBoard = [] {
        setBoard(constants::MED_BOARD_W, constants::MED_BOARD_H, constants::MED_BOARD_MINES);
        };
    static auto createLargeBoard = [] {
        setBoard(constants::LARGE_BOARD_W, constants::LARGE_BOARD_H, constants::LARGE_BOARD_MINES);
        };
    static auto createCustomBoard = [] {
        int mineCount = boardWidth * boardHeight * minePercent / 100;
        if (mineCount == 0) {
            mineCount += 2;
        } else if (mineCount == boardWidth * boardHeight) {
            mineCount -= 2;
        }
        setBoard(boardWidth, boardHeight, mineCount);
        };
    
    // for custom board modal component
    static Component widthSlider = Slider("", &boardWidth, 4, 50, 1);
    static Component heightSlider = Slider("", &boardHeight, 4, 50, 1);
    static Component mineSlider = Slider("", &minePercent, 1, 99, 1);
    Element sliderLabel(std::string labelText, int value) {
        return text(labelText + std::to_string(value));
    }
    static Component customBoardStart = Button("Start", createCustomBoard, ButtonOption::Animated());
    static Component customBoardQuit = Button("Back", hideCustomBoardModal, ButtonOption::Animated());

    /* FTXUI elements and components that do not change */
    static auto screen = ScreenInteractive::TerminalOutput();
    static auto exitGame = screen.ExitLoopClosure();

    // Modal component for exiting game
    static Component quitModalComponent = Container::Vertical({
            Button("Yes", exitGame, ButtonOption::Animated()),
            Button("No", hideQuitModal, ButtonOption::Animated()),
        })
        | Renderer([](Element buttons) {
            return vbox({
                text("Quit game?"),
                separator(),
                buttons
            })
            | border | bgcolor(Color::Black);;
        });
    
    static Component customBoardModalComponent = Container::Vertical({
        widthSlider,
        heightSlider,
        mineSlider,
        customBoardStart,
        customBoardQuit
    })
    | Renderer([](Element components) {
        return vbox({
            text("Create custom board"),
            separator(),
            gridbox({
                {sliderLabel("Width: ", boardWidth), widthSlider->Render()},
                {sliderLabel("Height: ", boardHeight), heightSlider->Render()},
                {sliderLabel("Mine %: ", minePercent), mineSlider->Render()}
            }) | xflex,
            separator(),
            customBoardStart->Render(),
            customBoardQuit->Render()
        })
        | border | bgcolor(Color::Black) | size(WIDTH, GREATER_THAN, screen.dimx() / 5);
    });

    // board buttons
    Component smallBoardButton = Button("Small (8x8, 10 mines)", createSmallBoard, ButtonOption::Animated());
    Component medBoardButton = Button("Medium (16x16, 40 mines)", createMedBoard, ButtonOption::Animated());
    Component largeBoardButton = Button("Large (30x16, 99 mines)", createLargeBoard, ButtonOption::Animated());
    Component customBoardButton = Button("Custom board", showCustomBoardModal, ButtonOption::Animated());
    // main menu component container
    static Component mainMenuButtons = Container::Vertical({
        Container::Horizontal({
            smallBoardButton,
            medBoardButton
        }),
        Container::Horizontal({
            largeBoardButton,
            customBoardButton
        })
    })
    | Renderer([](Element buttons) {
        return gridbox({
            {smallBoardButton->Render(), medBoardButton->Render()},
            {largeBoardButton->Render(), customBoardButton->Render()}
        }) | center | bgcolor(Color::Black);
    });

    // custom board modal menu
        // create 3 sliders that edit global integers, and a horizontal container with 2 buttons
    
    // start new game modal menu

    // return to menu modal menu

    /* FTXUI elements and components that do change */
    
    static Component windowBar {};
    static Component content {};
    static Component windowRenderer {};
    
    /* helper functions that edit the UI components that change throughout program execution */
    // window bar generator
    void setWindowBar() {
        windowBar = Button("Quit", showQuitModal, ButtonOption::Ascii())
            | Renderer([](Element button) {
                Element title = text("Terminal Minesweeper") | center;
                return hbox({
                    title,
                    separator(),
                    text(topBarSubtitle) | flex,
                    button
                });
        });
    }
    // sets content component to main menu buttons
    void setContentMainMenu() {
        content = mainMenuButtons;
        content |= Modal(customBoardModalComponent, &customBoardModalShown);
    }
    void setContentBoard(int width, int height, int mineCount) {
        // create board
        std::cout << width << 'x' << height << ", " << mineCount << "mines\n";
        content = Button("placeholder", [](){}, ButtonOption::Animated());
    }
    // window generator
    void setWindowRenderer() {
        windowRenderer = Container::Vertical({
            windowBar,
            content
        });
        windowRenderer |= Renderer([](Element window) {
            return vbox({
                windowBar->Render(),
                separator(),
                content->Render()
            }) | border;
        });
        windowRenderer |= Modal(quitModalComponent, &quitModalShown);
        windowRenderer |= bgcolor(Color::Black);
    }
    // game board generator

    /* interface functions to interact with UI */
    void setMainMenu() {
        changeMenuSubtitle("Main menu");
        setWindowBar();
        setContentMainMenu();
        setWindowRenderer();
        //auto content = Button("placeholder", [](){std::cout << "Pressed placeholder button";}, ButtonOption::Animated());
        //auto windowRenderer = createWindow(windowBar, content);
    }
    void setBoard(int width, int height, int mineCount) {
        changeMenuSubtitle("Flag the mines");
        setContentBoard(width, height, mineCount);
        setWindowRenderer();
        
        // needs this to allow new content to be interactive
        // for some reason the quit->yes option is not closing down the program properly after switching to the new board
        screen.ExitLoopClosure();
        startScreenLoop();
    }
    void changeMenuSubtitle(const std::string& subtitle) {
        topBarSubtitle = subtitle;
    }
    void startScreenLoop() {
        screen.Loop(windowRenderer);
    }
}