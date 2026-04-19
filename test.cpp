#include <iostream>
#include <buffer.hpp>
#include <cursor.hpp>
#include <view.hpp>
#include <tui.hpp>
#include <controller.hpp>

int main() {
    std::string file = "test.bin";

    core::Buffer buf(file);
    core::Cursor cur(buf.size() * 2); // nibble cursor
    render::View view;

    render::Editor editor(buf, cur, 16);

    auto screen = ftxui::ScreenInteractive::Fullscreen();

    auto renderer = ftxui::Renderer([&] {
        auto dhex = view.get_deq_hex(buf.get_data(), 0, buf.size());

        auto data = render::get_hbox(dhex, 16, cur.get_position());

        auto infofile = ftxui::text(file) | ftxui::border;

        return ftxui::vbox({
            data | ftxui::yflex,
            infofile
        });
    });
    auto app = ftxui::CatchEvent(renderer, [&](ftxui::Event event) {
    if (event == ftxui::Event::ArrowLeft) {
        editor.move_left();
        return true;
    }
    if (event == ftxui::Event::ArrowRight) {
        editor.move_right();
        return true;
    }
    if (event == ftxui::Event::ArrowUp) {
        editor.move_up();
        return true;
    }
    if (event == ftxui::Event::ArrowDown) {
        editor.move_down();
        return true;
    }

    if (event == ftxui::Event::Character('x')) {
        editor.delete_symbol();
        return true;
    }

    return false;
    });
    screen.Loop(app);
}
