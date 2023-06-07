#ifndef UI_HELPER_HPP
#define UI_HELPER_HPP

#include <functional>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;
namespace GameUI {
    class ModalPromptBuilder {
        public:
        static Component build(const std::string& prompt, std::function<void()> yes_op, std::function<void()> no_op);
    };
    Element build_text_element(const std::string& str);
}

#endif // UI_HELPER_HPP