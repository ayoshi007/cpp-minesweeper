#ifndef UI_HELPER_HPP
#define UI_HELPER_HPP

#include <functional>
#include <vector>
#include <string>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>


namespace GameUI {
    class Builder {
        

        public:
        static ftxui::Component build_modal_prompt(const std::string& prompt, std::function<void()> yes_op, std::function<void()> no_op);
        static ftxui::Element build_text_element(const std::string& str);
        static std::function<ftxui::Element(std::string, int)> slider_label;
        static ftxui::Component build_slider(std::string label_text, int* value, int min, int max, int increment);
    };
}

    #endif // UI_HELPER_HPP