#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <ui/window.hpp>

#include <iostream>

/*
Driver class
Start game by using game.cpp
*/

int main() {
    GameUI::Window::start();
    return 0;
}