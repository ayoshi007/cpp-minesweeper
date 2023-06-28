#ifndef UI_HELPER_HPP
#define UI_HELPER_HPP

#include <functional>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>


namespace GameUI {
    ftxui::Component build_modal_prompt(const std::string& prompt, std::function<void()> yes_op, std::function<void()> no_op);
    ftxui::Element build_text_element(const std::string& str);
}

#endif // UI_HELPER_HPP