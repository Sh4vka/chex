#pragma once
#include <iostream>
#include <deque>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/screen/screen.hpp>

namespace render {

ftxui::Element get_hbox(const std::deque<std::string> &hexdata, size_t len = 16);

ftxui::Element get_vbox(const std::deque<std::string> &hexdata, size_t len = 16);

}
