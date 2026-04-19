#pragma once
#include <buffer.hpp>
#include <cursor.hpp>

namespace render {

class Editor {
public:
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    
    void delete_byte();
    void insert_nibble(const char nibble);

    Editor(core::Buffer &buffer_, core::Cursor &cursor_, size_t bytes_per_row);

private :
    core::Cursor& cursor;
    core::Buffer& buffer;
    size_t bytes_per_row;
    bool has_pending;
};

}
