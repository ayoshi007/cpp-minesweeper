/*
Handle FTXUI
Includes UI of:
- game board
- main menu
- custom board menu
- game over/win screen
*/
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen/hpp>
#include <ftxui/component/component.hpp> // Button
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/color.hpp>
#include <string>

void pickBoard() {
    Element menu
}

ftxui::Element menuHeader(std::string title) {
    auto elements = vbox(
        {
            hbox({
                text(title),
                filler(),
                quitButton()
            })
        }
    )
    return elements;
}
Button quitButton() {
    auto modalComponent = Container::Vertical({
        text("Quit?"),
        Button("Yes"),
        Button("No")
    })
}