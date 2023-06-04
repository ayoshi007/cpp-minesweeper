#include <my_minesweeper/core/constants.hpp>

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/element.hpp>
#include <ftxui/component/screen_interactive.hpp>

namespace GameUI {
    namespace MainMenu {
        chosen_width = constants::SMALL_BOARD_W;
        chosen_height = constants::SMALL_BOARD_H;
        chosen_mine_count = constants::SMALL_BOARD_MINES;
        board_chosen = false;
        mine_percent = constants::DEFAULT_CUSTOM_MINE_PERCENT;

        custom_board_modal_shown = false;

        create_small_board = [&] {
            chosen_width = constants::SMALL_BOARD_W;
            chosen_height = constants::SMALL_BOARD_H;
            chosen_mine_count = constants::SMALL_BOARD_MINES;
            board_chosen = true;
        }
        create_med_board = [&] {
            chosen_width = constants::MED_BOARD_W;
            chosen_height = constants:MED_BOARD_H;
            chosen_mine_count = constants::MED_BOARD_MINES;
            board_chosen = true;
        }
        create_large_board = [&] {
            chosen_width = constants::LARGE_BOARD_W;
            chosen_height = constants::LARGE_BOARD_H;
            chosen_mine_count = constants::LARGE_BOARD_MINES;
            board_chosen = true;
        }
        create_custom_board = [&] {
            chosen_mine_count = chosen_board_width * chosen_board_height * mine_percent / 100;
            if (chosen_mine_count == 0) {
                chosen_mine_count += 2;
            } else if (chosen_mine_count == chosen_board_width * chosen_board_height) {
                chosen_mine_count -= 2;
            }
            board_chosen = true;
        }
        show_custom_board_modal = [&] { custom_board_modal_shown = true; };
        hide_custom_board_modal = [&] { custom_board_modal_shown = false; };

        slider_label = [] (const std::string& label, int value) {
            return text(labelText + std::to_string(value)); 
        }

        small_board_button = Button("Small (8x8, 10 mines)", create_small_board, ButtonOption::Animated());
        medium_board_button = Button("Medium (16x16, 40 mines)", create_med_board, ButtonOption::Animated());
        large_board_button = Button("Large (30x16, 99 mines)", create_large_board, ButtonOption::Animated());
        custom_board_button = Button("Custom board", show_custom_board_modal, ButtonOption::Animated());

        width_slider = Slider("", &chosen_width, 4, 50, 1);
        height_slider = Slider("", &chosen_height, 4, 50, 1);;
        mine_percent_slider = Slider("", &mine_percent, 1, 99, 1);;
        custom_board_start = Button("Start", create_custom_board, ButtonOption::Animated());
        custom_board_quit = Button("Back", hide_custom_board_modal, ButtonOption::Animated());
        custom_menu_modal_component = Container::Vertical({
            width_slider,
            height_slider,
            mine_percent_slider,
            custom_board_start,
            custom_board_quit
        });
        
        main_menu_buttons = Container::Vertical({
            Container::Horizontal({
                small_board_button,
                medium_board_button
            }),
            Container::Horizontal({
                large_board_button,
                custom_board_button
            })
        });

        custom_board_modal_renderer = Renderer(custom_menu_modal_component, [&] {
            return vbox({
                text("Create custom board"),
                separator(),
                gridbox({
                    {slider_label("Width: ", chosen_width), width_slider->Render()},
                    {slider_label("Height: ", chosen_height), height_slider->Render()},
                    {slider_label("Mine %: ", mine_percent), mine_percent_slider->Render()}
                }) | xflex,
                separator(),
                custom_board_start->Render(),
                custom_board_quit->Render()
            });
        })
        | border
        | bgcolor(Color::Black)
        | size(WIDTH, GREATER_THAN, ScreenInteractive::Active()->dimx() / 5);

        main_menu_buttons_renderer = Renderer(main_menu_buttons, [&] {
            return gridbox({
                {small_board_button->Render(), med_board_button->Render()},
                {large_board_button->Render(), custom_board_button->Render()}
            }) | center | bgcolor(Color::Black);
        }) | Modal(custom_board_modal_renderer, &custom_board_modal_shown);
    }
}