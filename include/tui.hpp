#pragma once
#include <iostream>
#include <deque>
#include <cursor.hpp>
#include <controller.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/screen/screen.hpp>

namespace render {

ftxui::Element get_hbox(const std::deque<std::string> &hexdata, core::Cursor &cursor, const size_t len = 16);

ftxui::Element metadata(const Editor::Mode mode, const std::string filename, const std::string command);

ftxui::Element get_vbox(const std::deque<std::string> &hexdata, size_t len = 16);

}
