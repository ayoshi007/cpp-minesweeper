#include <doctest/doctest.h>

#include <functional>
#include <vector>
#include <string>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/util/ref.hpp>

#include <ui/ui_helper.hpp>

using namespace ftxui;

namespace GameUI {
    std::function<Element(std::string, int)> Builder::slider_label = [] (std::string label_text, int value) {
        return text(label_text + std::to_string(value));
    };
    Component Builder::build_slider(std::string label_text, int* value, int min, int max, int increment) {
        return Slider(label_text, Ref(value), ConstRef(min), ConstRef(max), ConstRef(increment));
    }
    Component Builder::build_modal_prompt(const std::string& prompt, std::function<void()> yes_op, std::function<void()> no_op) {
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
    
    Element Builder::build_text_element(const std::string& str) {
        return text(str);
    }
}

#ifdef RUN_UI_TESTS
TEST_SUITE("UI helper functions") {
    ScreenInteractive screen = ScreenInteractive::TerminalOutput();
    TEST_CASE("Build text element") {
        MESSAGE("Text element builder test");
        Element text_element = GameUI::Builder::build_text_element("Text element");
        Component renderer = Renderer([&] () {
            return text_element;
        })
        | border;
        screen.Loop(renderer);
    }
    TEST_CASE("Build modal prompt") {
        MESSAGE("Modal prompt builder interactive test");
        bool show_modal = false;
        Component show_modal_button = Button("Show modal", [&show_modal] { show_modal = true; }, ButtonOption::Ascii());
        Component modal_comp = GameUI::Builder::build_modal_prompt("End test?", screen.ExitLoopClosure(), [&show_modal] { show_modal = false; });
        Component renderer = Renderer(show_modal_button, [&] () {
            return show_modal_button->Render();
        })
        | Modal(modal_comp, &show_modal)
        | border;
        screen.Loop(renderer);
    }
    TEST_CASE("Test individual slider label builders") {
        MESSAGE("Slider builder and label builder interactive test");
        int value = 50;
        int min = 4;
        int max = 100;
        int increment = 1;
        std::string label_text = "Value: ";
        Component slider = GameUI::Builder::build_slider("", &value, min, max, increment);
        Component container = Container::Vertical({slider});
        Component renderer = Renderer(container, [&] () {
            return hbox(
                {GameUI::Builder::slider_label(label_text, value), slider->Render()}
            );
        })
        | border;
        screen.Loop(renderer);
    }
}
#endif