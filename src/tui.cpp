#include <tui.hpp>

namespace render {

    ftxui::Element get_hbox(const std::deque<std::string> &hexdata, size_t len) {
        std::deque<ftxui::Element> rows;
        std::deque<ftxui::Element> current_row;
        std::deque<ftxui::Element> address;
        size_t local_adr = 0;
        for (size_t i = 0; i < hexdata.size(); ++i) {
            current_row.push_back(ftxui::text(hexdata[i]));
            if ((i + 1) % len != 0 && i != hexdata.size() - 1) {
                local_adr++;
                current_row.push_back(ftxui::text(" "));
            }
            if ((i + 1) % len == 0 || i == hexdata.size() - 1) {
                rows.push_back(ftxui::hbox(current_row));
                local_adr++;
                address.push_back(ftxui::text(std::format("{0:#x}", local_adr)));
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
