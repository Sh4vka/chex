#include <controller.hpp>
#include <buffer.hpp>
#include <cursor.hpp>
#include <cstdint>

namespace render {
    
void Editor::move_left() {cursor.move_left(1);}
void Editor::move_right() {cursor.move_right(1);}
void Editor::move_up() {cursor.move_left(bytes_per_row * 2);}
void Editor::move_down() {cursor.move_right(bytes_per_row * 2);}

void Editor::delete_byte() {buffer.erase_byte(cursor.get_position() / 2);}

void Editor::insert_nibble(const char nibble) {
    if (!isxdigit(nibble)) return;
    uint8_t value = 
        (nibble >= '0' && nibble <= '9') ? nibble - '0' : 
        (nibble >= 'a' && nibble <= 'f') ? nibble - 'a' + 10 :
        (nibble >= 'A' && nibble <= 'F') ? nibble - 'A' + 10 : 0;
    if (cursor.get_position() >= cursor.get_max_position()) {buffer.insert_byte(static_cast<unsigned char>(0x00), cursor.get_position() / 2);}
    if (!has_pending) {
        buffer.insert_byte(static_cast<unsigned char>(value << 4), cursor.get_position() / 2);
        has_pending = true;
        move_right();
    }
    else {
        uint8_t curval = static_cast<uint8_t>(buffer.get_byte(cursor.get_position() / 2));

        buffer.insert_byte(static_cast<unsigned char>(buffer.get_byte(curval << 4 | value)), cursor.get_position() / 2);
        move_right();
        has_pending = false;
    }
    cursor.set_max_position(cursor.get_max_position() * 2 - 1);
}

Editor::Editor(core::Buffer &buffer_, core::Cursor &cursor_, size_t bytes_per_row_) : buffer(buffer_), cursor(cursor_), bytes_per_row(bytes_per_row_), has_pending(false) {}
}
