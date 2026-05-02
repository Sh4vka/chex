#include <buffer.hpp>
#include <cursor.hpp>
#include <view.hpp>
#include <tui.hpp>
#include <controller.hpp>

static constexpr size_t byte_in_line = 16u;

int main(int argc, char* argv[]) {
    if (argc == 0) {return 1;}
    std::string file(argv[1]);
 
    core::Buffer buffer(file);
    core::Cursor cursor(buffer.size() * 2);
    render::View view;
    render::Editor editor(buffer, cursor, byte_in_line);

    auto screen = ftxui::ScreenInteractive::Fullscreen();
    auto renderer = ftxui::Renderer([&] {
        auto dhex = view.get_deq_hex(buffer.get_data(), 0, buffer.size());
        auto data = render::get_hbox(dhex, cursor, byte_in_line);
        auto infofile = ftxui::text(file) | ftxui::border;
        return ftxui::vbox({data | ftxui::yflex, infofile });
    });
    auto app = ftxui::CatchEvent(renderer, [&](ftxui::Event e) {
        editor.event(e);
        return true;
    });
    screen.Loop(app);
    return 0;
}
