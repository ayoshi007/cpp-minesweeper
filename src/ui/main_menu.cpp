#include <doctest/doctest.h>

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>

#include <ui/main_menu.hpp>
#include <ui/ui_helper.hpp>
#include <core/constants.hpp>

using namespace ftxui;

namespace GameUI {
    int MainMenuBuilder::width_slider_value = constants::DEFAULT_CUSTOM_W;
    int MainMenuBuilder::height_slider_value = constants::DEFAULT_CUSTOM_H;
    int MainMenuBuilder::mine_percent_slider_value = constants::DEFAULT_CUSTOM_PERCENT;

    int MainMenuBuilder::get_width_slider_value() { return width_slider_value; }
    int MainMenuBuilder::get_height_slider_value() { return height_slider_value; }
    int MainMenuBuilder::get_mine_percent_slider_value() { return mine_percent_slider_value; }
    /**
     * Builds the modal menu for creating a custom board
    */
    Component MainMenuBuilder::build_custom_board_modal(std::function<void()> custom_board_action) {
        // create sliders
        Component width_slider = GameUI::PartsBuilder::build_slider("", &width_slider_value, 4, 100, 1);
        Component height_slider = GameUI::PartsBuilder::build_slider("", &height_slider_value, 4, 100, 1);
        Component mine_percent_slider_slider = GameUI::PartsBuilder::build_slider("", &mine_percent_slider_value, 1, 99, 1);
        // create buttons to start the game or quit the modal
        Component custom_board_start = Button("Start", custom_board_action, ButtonOption::Animated());
        Component custom_board_quit = Button("Back", []{ MainMenuBuilder::custom_board_menu_shown = false; }, ButtonOption::Animated());
        // create and return the renderer for the modal menu
        return Container::Vertical({
            width_slider,
            height_slider,
            mine_percent_slider_slider,
            custom_board_start,
            custom_board_quit
        })
        | Renderer([=] (Element components) {
            (void)components;
            return vbox({
                text("Create custom board"),
                separator(),
                gridbox({
                    {GameUI::PartsBuilder::slider_label("Width: ", MainMenuBuilder::width_slider_value), width_slider->Render()},
                    {GameUI::PartsBuilder::slider_label("Height: ", MainMenuBuilder::height_slider_value), height_slider->Render()},
                    {GameUI::PartsBuilder::slider_label("Mine %: ", MainMenuBuilder::mine_percent_slider_value), mine_percent_slider_slider->Render()}
                }) | xflex,
                separator(),
                custom_board_start->Render(),
                custom_board_quit->Render()
            })
            | border | bgcolor(Color::Black);// | size(WIDTH, GREATER_THAN, screen.dimx() / 5);
        });
    }
    /**
     * Builds the main menu's grid of buttons
    */
    Component MainMenuBuilder::build_main_menu_buttons(
        std::function<void()> small_board_action,
        std::function<void()> med_board_action,
        std::function<void()> large_board_action
    ) {
        // create buttons
        Component small_board_button = Button(constants::SMALL_BOARD_BUTTON_LABEL, small_board_action, ButtonOption::Animated());
        Component med_board_button = Button(constants::MED_BOARD_BUTTON_LABEL, med_board_action, ButtonOption::Animated());
        Component large_board_button = Button(constants::LARGE_BOARD_BUTTON_LABEL, large_board_action, ButtonOption::Animated());
        Component custom_board_button = Button(constants::CUSTOM_BOARD_BUTTON_LABEL, [] { MainMenuBuilder::custom_board_menu_shown = true; }, ButtonOption::Animated());
        // create and return the renderer for the buttons
        return Container::Vertical({
            Container::Horizontal({
                small_board_button,
                med_board_button
            }),
            Container::Horizontal({
                large_board_button,
                custom_board_button
            })
        })
        | Renderer([=](Element buttons) {
            (void)buttons;
            return gridbox({
                {small_board_button->Render(), med_board_button->Render()},
                {large_board_button->Render(), custom_board_button->Render()}
            }) | center | bgcolor(Color::Black);
        });
    }
    Component MainMenuBuilder::build_main_menu_renderer(
        std::function<void()> small_board_action,
        std::function<void()> med_board_action,
        std::function<void()> large_board_action,
        std::function<void()> custom_board_action
    ) {
        // get the modal menu
        Component custom_board_modal = build_custom_board_modal(custom_board_action);
        // get the buttons
        Component main_menu_buttons = build_main_menu_buttons(small_board_action, med_board_action, large_board_action);
        // attach the modal menu to the buttons
        main_menu_buttons |= Modal(custom_board_modal, &custom_board_menu_shown);
        return main_menu_buttons;
    }
}

#ifdef RUN_UI_TESTS
TEST_SUITE("Main menu builder functions") {
    TEST_CASE("Interactive main menu test") {
        ScreenInteractive screen = ScreenInteractive::TerminalOutput();
        MESSAGE("Testing main menu");

        auto quit_button = Button("End", screen.ExitLoopClosure(), ButtonOption::Animated());
        auto button_container = Container::Vertical({
            quit_button
        });

        int width_value = constants::DEFAULT_CUSTOM_W;
        int height_value = constants::DEFAULT_CUSTOM_W;
        int mine_count = constants::SMALL_BOARD_MINES;
        Component main_menu_renderer = GameUI::MainMenuBuilder::build_main_menu_renderer(
            [&]{
                width_value = constants::SMALL_BOARD_W;
                height_value = constants::SMALL_BOARD_H;
                mine_count = constants::SMALL_BOARD_MINES;
            },
            [&]{
                width_value = constants::MED_BOARD_W;
                height_value = constants::MED_BOARD_H;
                mine_count = constants::MED_BOARD_MINES;
            },
            [&]{
                width_value = constants::LARGE_BOARD_W;
                height_value = constants::LARGE_BOARD_H;
                mine_count = constants::LARGE_BOARD_MINES;
            },
            [&]{
                width_value = GameUI::MainMenuBuilder::get_width_slider_value();
                height_value = GameUI::MainMenuBuilder::get_height_slider_value();
                int mine_percent = GameUI::MainMenuBuilder::get_mine_percent_slider_value();
                mine_count = width_value * height_value * mine_percent / 100;
                if (mine_count == 0) {
                    mine_count += 2;
                } else if (width_value * height_value - 10 < mine_count) {
                    mine_count = width_value * height_value - 10;
                }
            }
        );

        auto renderer = Container::Vertical({
            button_container,
            main_menu_renderer
        })
        | Renderer([&] (Element e) {
            return vbox({
                e,
                text("W: " + std::to_string(width_value) + ", H: " + std::to_string(height_value) + ", Mines: " + std::to_string(mine_count))
            });
        });
        screen.Loop(renderer);
    }
}
#endif