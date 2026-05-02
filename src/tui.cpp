#include <tui.hpp>

namespace render {

ftxui::Element get_hbox(const std::deque<std::string> &hexdata, core::Cursor &cursor, const size_t len) {
    std::deque<ftxui::Element> rows;
    std::deque<ftxui::Element> current_row;
    std::deque<ftxui::Element> address;

    size_t row = 0;
    size_t byte_index = cursor.byte();
    size_t nibble = cursor.nibble_index();

    for (size_t i = 0; i < hexdata.size(); ++i) {
        std::string byte = hexdata[i];
        auto left = ftxui::text(std::string(1, byte[0]));
        auto right = ftxui::text(std::string(1, byte[1]));
        if (i == byte_index) {
            if (nibble == 0) {left = left | ftxui::inverted;}
            else {right = right | ftxui::inverted;}
        }
        current_row.push_back(ftxui::hbox({left, right}));
        if ((i + 1) % len != 0)
            current_row.push_back(ftxui::text(" "));

        if ((i + 1) % len == 0 || i == hexdata.size() - 1) {
            rows.push_back(ftxui::hbox(current_row));
            address.push_back(ftxui::text(std::format("{:#08x}", row * len)));
            row++;
            current_row.clear();
        }
    }
    auto data = ftxui::vbox(rows) | ftxui::border;
    auto addr = ftxui::vbox(address) | ftxui::border;
    return ftxui::hbox(addr, data);
}

ftxui::Element get_vbox(const std::deque<std::string> &hexdata, size_t len) {
    std::deque<ftxui::Element> rows;
    std::deque<ftxui::Element> current_row;
    for (size_t i = 0; i < hexdata.size(); ++i) {
        current_row.push_back(ftxui::text(hexdata[i]));
        if ((i + 1) % len != 0 && i != hexdata.size() - 1) {
            current_row.push_back(ftxui::text(" "));
        }
        if ((i + 1) % len == 0 || i == hexdata.size() - 1) {
            rows.push_back(ftxui::hbox(current_row));
            current_row.clear();
        }
    }
    return ftxui::vbox(rows);
}

}
