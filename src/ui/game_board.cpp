#include <ui/game_board.hpp>
#include <ui/ui_helper.hpp>

#include <doctest/doctest.h>

#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/canvas.hpp>


#ifdef RUN_UI_TESTS
TEST_SUITE("Game board builder functions") {
    TEST_CASE("Interactive game board test" * doctest::skip()) {
        ScreenInteractive screen = ScreenInteractive::TerminalOutput();
        MESSAGE("Testing game board");
    }
}
#endif