#ifndef UI_HELPER_HPP
#define UI_HELPER_HPP

#include <functional>
#include <ftxui/component/component.hpp>

using namespace ftxui;
namespace GameUI {
    class ModalPromptBuilder {
        public:
        static Component build(const std::string& prompt, std::function<void()> yes_op, std::function<void()> no_op);
    };
}

#endif // UI_HELPER_HPP