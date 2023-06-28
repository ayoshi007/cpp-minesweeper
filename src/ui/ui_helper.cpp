#include <doctest/doctest.h>

#include <functional>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>

#include <ui/ui_helper.hpp>

using namespace ftxui;

namespace GameUI {
    Component build_modal_prompt(const std::string& prompt, std::function<void()> yes_op, std::function<void()> no_op) {
        return Container::Vertical({
            Button("Yes", yes_op, ButtonOption::Animated()),
            Button("No", no_op, ButtonOption::Animated())
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
    
    Element build_text_element(const std::string& str) {
        return text(str);
    }
}

#ifdef RUN_UI_TESTS
TEST_SUITE("UI helper functions") {
    ScreenInteractive screen = ScreenInteractive::TerminalOutput();
    TEST_CASE("Build modal prompt") {
        MESSAGE("Modal prompt builder interactive test");
        bool show_modal = false;
        Component show_modal_button = Button("Show modal", [&show_modal] { show_modal = true; });
        Component modal_comp = GameUI::build_modal_prompt("End test?", screen.ExitLoopClosure(), [&show_modal] { show_modal = false; });
        Component renderer = Renderer(show_modal_button, [&] () {
            return show_modal_button->Render();
        })
        | Modal(modal_comp, &show_modal)
        | border;
        screen.Loop(renderer);
    }
}
#endif