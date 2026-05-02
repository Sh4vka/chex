#include <controller.hpp>
#include <buffer.hpp>
#include <cursor.hpp>
#include <cstdint>

namespace render {
    
void Editor::move_left() {cursor.move(-1);}
void Editor::move_right() {cursor.move(1);}
void Editor::move_up() {cursor.move(-bytes_per_row * 2);}
void Editor::move_down() {cursor.move(bytes_per_row * 2);}

void Editor::delete_byte() {
    size_t idx = cursor.byte();

    if (idx >= buffer.size()) return;

    buffer.erase_byte(idx);

    cursor.set_max_position(buffer.size() ? buffer.size() * 2 - 1 : 0);
    cursor.move(0);
    has_pending = false;
}

void Editor::insert_nibble(const char nibble_char) {
    if (!isxdigit(nibble_char)) return;

    uint8_t value =
        (nibble_char >= '0' && nibble_char <= '9') ? nibble_char - '0' :
        (nibble_char >= 'a' && nibble_char <= 'f') ? nibble_char - 'a' + 10 :
        (nibble_char >= 'A' && nibble_char <= 'F') ? nibble_char - 'A' + 10 : 0;

    size_t byte_index = cursor.byte();
    auto& data = buffer.get_data();

    if (byte_index >= data.size()) {
        data.push_back(0x00);
    }

    if (!has_pending) {
        data.insert(data.begin() + byte_index, value << 4);
        pending = value;
        has_pending = true;
    } else {
        data[byte_index] = (pending << 4) | value;
        has_pending = false;
    }

    cursor.move(+1);
    cursor.set_max_position(data.size() ? data.size() * 2 - 1 : 0);
}

Editor::Editor(core::Buffer &buffer_,
               core::Cursor &cursor_,
               size_t bytes_per_row_)
    : buffer(buffer_),
      cursor(cursor_),
      bytes_per_row(bytes_per_row_),
      has_pending(false),
      pending(0){}
}
