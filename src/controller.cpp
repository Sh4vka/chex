#include <controller.hpp>
#include <buffer.hpp>
#include <cursor.hpp>

namespace render {
    
void Editor::move_left() {cursor.move_left(1);}
void Editor::move_right() {cursor.move_right(1);}
void Editor::move_up() {cursor.move_left(bytes_per_row * 2);}
void Editor::move_down() {cursor.move_right(bytes_per_row * 2);}

void Editor::delete_symbol() {buffer.erase_byte(cursor.get_position() * 2);}

Editor::Editor(core::Buffer &buffer_, core::Cursor &cursor_, size_t bytes_per_row_) : buffer(buffer_), cursor(cursor_), bytes_per_row(bytes_per_row_) {}
}
