#include <buffer.hpp>
#include <cursor.hpp>
#include <view.hpp>
#include <viewport.hpp>
#include <tui.hpp>
#include <controller.hpp>

int main(int argc, char* argv[]) {
    if (argc == 0) {return 1;}
    std::string file(argv[1]);

    core::Buffer buffer(file);
    core::Cursor cursor(buffer.size() * 2);
    render::View view;
    render::Viewport viewport;
    render::Editor editor(buffer, cursor, viewport);

    ftxui::Box data_box;
    auto screen = ftxui::ScreenInteractive::Fullscreen();

    auto renderer = ftxui::Renderer([&] {
        if (data_box.y_max > data_box.y_min) {
            size_t new_rows = (size_t)(data_box.y_max - data_box.y_min - 1);
            viewport.rows = new_rows > 0 ? new_rows : 1;
        }
        size_t start = viewport.offset;
        size_t end = std::min(start + viewport.rows * viewport.bytes_per_row, buffer.size());
        auto dhex = view.get_deq_hex(buffer.get_data(), start, end);
        auto data = render::get_hbox(dhex, cursor, viewport.bytes_per_row, viewport.offset)
                    | ftxui::reflect(data_box);
        auto infodata = render::metadata(editor.get_mode(), file, editor.command());
        auto info = infodata | ftxui::border;
        return ftxui::vbox({data | ftxui::yflex, info});
    });

    auto app = ftxui::CatchEvent(renderer, [&](ftxui::Event e) {
        editor.event(e);
        return true;
    });

    screen.Loop(app);
    return 0;
}
