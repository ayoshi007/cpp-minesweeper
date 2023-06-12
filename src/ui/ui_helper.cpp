#include <functional>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>

#include <ui/ui_helper.hpp>

using namespace ftxui;
Component GameUI::ModalPromptBuilder::build(const std::string& prompt, std::function<void()> yes_op, std::function<void()> no_op) {
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
Element GameUI::build_text_element(const std::string& str) {
    return text(str);
}