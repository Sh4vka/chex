#include <iostream>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/screen/screen.hpp>
#include "buffer.hpp"
#include "cursor.hpp"
#include "view.hpp"

int main() {
    std::string file = "test.bin";
    core::Buffer buf(file);
    core::Cursor cur(buf.size());
    render::View view;
    std::string hex = view.get_string_hex(buf.get_data(), 0, buf.size());
    std::string src = "";
    for (size_t i = 0; i < hex.size(); ++i) {
        src.push_back(hex[i]);
        i++;
        src.push_back(hex[i]);
        src.push_back(' ');
    }
    auto data = ftxui::paragraph(src) | ftxui::border;
    auto infofile = ftxui::text(file) | ftxui::border;

    auto elements = ftxui::vbox({data | ftxui::yflex, infofile});
    auto render = ftxui::Renderer([&] {return elements;});
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    screen.Clear();
    screen.Loop(render);
    return 0;
}
