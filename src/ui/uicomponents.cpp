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
    /* FTXUI elements and components that do not change */
    static ScreenInteractive screen = ScreenInteractive::TerminalOutput();
    static auto exitGame = screen.ExitLoopClosure();
    static auto sliderLabel = [] (std::string labelText, int value) {
        return text(labelText + std::to_string(value));
    };
    static auto createSmallBoard = [] {
        boardMineCount = constants::SMALL_BOARD_MINES;
        showBoard();
    };
    static auto createMedBoard = [] {
        boardMineCount = constants::MED_BOARD_MINES;
        showBoard();
    };
    static auto createLargeBoard = [] {
        boardMineCount = constants::LARGE_BOARD_MINES;
        showBoard();
    };
    static auto createCustomBoard = [] {
        int mineCount = boardWidth * boardHeight * minePercent / 100;
        if (mineCount == 0) {
            mineCount += 2;
        } else if (mineCount == boardWidth * boardHeight) {
            mineCount -= 2;
        }
        boardMineCount = mineCount;
        showBoard();
    };
    /* functors and variables */
    static bool quitModalShown = false;
    static bool customBoardModalShown = false;
    static int boardWidth {constants::DEFAULT_CUSTOM_W};
    static int boardHeight {constants::DEFAULT_CUSTOM_H};
    static int minePercent {constants::DEFAULT_CUSTOM_PERCENT};
    static int boardMineCount {constants::SMALL_BOARD_MINES};

    static int shownScreen {0};
    
    static auto showQuitModal = [] { quitModalShown = true; };
    static auto hideQuitModal = [] { quitModalShown = false; };
    static auto showCustomBoardModal = [] { customBoardModalShown = true; };
    static auto hideCustomBoardModal = [] { customBoardModalShown = false; };
    
    static auto showMainMenu = [] { shownScreen = 0; };
    static auto showBoard  = [] { shownScreen = 1; };

    static Component quitButton = Button("Quit", showQuitModal, ButtonOption::Ascii());
    // modal component for custom board creation
    static Component widthSlider = Slider("", &boardWidth, 4, 50, 1);
    static Component heightSlider = Slider("", &boardHeight, 4, 50, 1);
    static Component mineSlider = Slider("", &minePercent, 1, 99, 1);
    static Component customBoardStart = Button("Start", createCustomBoard, ButtonOption::Animated());
    static Component customBoardQuit = Button("Back", hideCustomBoardModal, ButtonOption::Animated());
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

    class ComponentRendererFactory {
        public:
        static Component makeYesNoModal(const std::string& prompt, std::function<void()> yesOp, std::function<void()> noOp) {
            return Container::Vertical({
                Button("Yes", yesOp, ButtonOption::Animated()),
                Button("No", noOp, ButtonOption::Animated())
            })
            | Renderer([prompt](Element buttons) {
                return vbox({
                    text(prompt),
                    separator(),
                    buttons
                })
                | border | bgcolor(Color::Black);
            });
        }
        static Component makeWindowBarRenderer(const std::string& subtitle, Component quitButton) {
            return quitButton
                | Renderer([subtitle](Element button) {
                    return hbox({
                        text("Terminal Minesweeper") | center,
                        separator(),
                        text(subtitle) | flex,
                        button
                });
            });
        }
    };
    static auto constructWindowRenderer = [] (const std::string& subtitle, Component& content) {
        static Component window = Container::Vertical({
            ComponentRendererFactory::makeWindowBarRenderer(subtitle, quitButton),
            content
        });
        static Component windowRenderer = Renderer(window, []() {
            return vbox({
                window->ChildAt(0)->Render(),
                separator(),    
                window->ChildAt(1)->Render()
            }) | border;
        });
        windowRenderer |= Modal(ComponentRendererFactory::makeYesNoModal("Quit game?", exitGame, hideQuitModal), &quitModalShown);
        windowRenderer |= bgcolor(Color::Black);
        return windowRenderer;
    };
    Component constructMainMenu() {
        // modal component for custom board creation
        static Component widthSlider = Slider("", &boardWidth, 4, 50, 1);
        static Component heightSlider = Slider("", &boardHeight, 4, 50, 1);
        static Component mineSlider = Slider("", &minePercent, 1, 99, 1);
        static Component customBoardStart = Button("Start", createCustomBoard, ButtonOption::Animated());
        static Component customBoardQuit = Button("Back", hideCustomBoardModal, ButtonOption::Animated());
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

        // main menu buttons
        static Component smallBoardButton = Button("Small (8x8, 10 mines)", createSmallBoard, ButtonOption::Animated());
        static Component medBoardButton = Button("Medium (16x16, 40 mines)", createMedBoard, ButtonOption::Animated());
        static Component largeBoardButton = Button("Large (30x16, 99 mines)", createLargeBoard, ButtonOption::Animated());
        static Component customBoardButton = Button("Custom board", showCustomBoardModal, ButtonOption::Animated());
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
        }) | Modal(customBoardModalComponent, &customBoardModalShown);

        return constructWindowRenderer("Main menu", mainMenuButtons);
    }

    Component constructBoard() {
        static Component board = Button(
            "W: " + std::to_string(boardWidth) + ", H: " + std::to_string(boardHeight) + ", Mines: " + std::to_string(boardMineCount),
            [](){}, ButtonOption::Animated()
        );
        return constructWindowRenderer("Flag the mines!", board);
    }

    Component parentContainer;
    
    /* interface functions to interact with UI */
    void initializeContainer() {
        static Component mainMenuRenderer = constructMainMenu();
        static Component boardRenderer = constructBoard();
        static Component screens = Container::Tab({
            mainMenuRenderer,
            boardRenderer
        }, &shownScreen);
        parentContainer = Renderer(screens, [] {
            Element displayed = mainMenuRenderer->Render() | center;
            if (shownScreen == 1) {
                displayed = dbox({
                    boardRenderer->Render() | clear_under | center
                });
            }

            return displayed;
        });
    }
    void startGame() {
        screen.Loop(parentContainer);
    }
}