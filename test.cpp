#include <iostream>
#include <buffer.hpp>
#include <cursor.hpp>
#include <view.hpp>
#include <tui.hpp>

int main() {
    std::string file = "test.bin";
    core::Buffer buf(file);
    core::Cursor cur(buf.size());
    render::View view;
    std::deque<std::string> dhex = view.get_deq_hex(buf.get_data(), 0, buf.size());

    auto data = render::get_hbox(dhex);

    auto infofile = ftxui::text(file) | ftxui::border;

    auto elements = ftxui::vbox({data | ftxui::yflex, infofile});
    auto render = ftxui::Renderer([&] {return elements;});
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    screen.Clear();
    screen.Loop(render);
    return 0;
}
