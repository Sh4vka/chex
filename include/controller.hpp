#pragma once
#include <buffer.hpp>
#include <cursor.hpp>
#include <ftxui/component/event.hpp>
#include <string>

namespace render {

class Editor {
public:
    enum class Mode : uint8_t {
        NORMAL,
        VISUAL,
        INSERT,
        COMMAND,
        SEARCH
    };
    
    void event(ftxui::Event e);

    Editor(core::Buffer &buffer_, core::Cursor &cursor_, size_t bytes_per_row);

private :
    core::Cursor& cursor;
    core::Buffer& buffer;
    size_t bytes_per_row;
    bool has_pending;
    uint8_t pending;
    std::string command_buffer;
    Mode mode;

    void event_normal(ftxui::Event e);
    void event_insert(ftxui::Event e);
    void event_visual(ftxui::Event e);
    void event_command(ftxui::Event e);
    void event_search(ftxui::Event e);

    void execute_command();

    void move_left();
    void move_right();
    void move_up();
    void move_down();
    
    void delete_byte();
    void insert_nibble(const char nibble);

    void save();
    void quit();
};

}
