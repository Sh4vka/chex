#include <controller.hpp>
#include <buffer.hpp>
#include <cursor.hpp>
#include <tui.hpp>
#include <ftxui/component/event.hpp>
#include <cstdint>
#include <string>

namespace render {

void Editor::event(ftxui::Event e) {
    switch (mode) {
        case Mode::NORMAL:
            event_normal(e);
            break;

        case Mode::VISUAL:
            event_visual(e);
            break;

        case Mode::INSERT:
            event_insert(e);
            break;

        case Mode::COMMAND:
            event_command(e);
            break;

        case Mode::SEARCH:
            event_search(e);
            break;
    }
}

void Editor::event_normal(ftxui::Event e) {
    if (e == ftxui::Event::ArrowRight) {
        move_right();
        return;
    }

    if (e == ftxui::Event::ArrowLeft) {
        move_left();
        return;
    }

    if (e == ftxui::Event::ArrowUp) {
        move_up();
        return;
    }

    if (e == ftxui::Event::ArrowDown) {
        move_down();
        return;
    }

    if (e == ftxui::Event::Character('i')) {
        mode = Mode::INSERT;
        return;
    }

    if (e == ftxui::Event::Character('v')) {
        mode = Mode::VISUAL;
        return;
    }

    if (e == ftxui::Event::Character(':')) {
        mode = Mode::COMMAND;
        return;
    }

    if (e == ftxui::Event::Character('/')) {
        mode = Mode::SEARCH;
        return;
    }

    if (e == ftxui::Event::Character('x')) {
        delete_byte();
        return;
    }
}

void Editor::event_insert(ftxui::Event e) {
    if (e == ftxui::Event::Escape) {
        mode = Mode::NORMAL;
        has_pending = false;
        return;
    }
    if (e.is_character()) {insert_nibble(e.character()[0]);}
}

void Editor::event_command(ftxui::Event e) {
    if (e == ftxui::Event::Escape) {
        mode = Mode::NORMAL;
        return;
    }

    if (e == ftxui::Event::Return) {
        execute_command();
        mode = Mode::NORMAL;
        return;      
    }

    if (e == ftxui::Event::Backspace) {
        if (!command_buffer.empty()) {command_buffer.pop_back();}
        return;
    }
    if (e.is_character()) {command_buffer += e.character();}
    return;
}

void Editor::event_visual(ftxui::Event e) {
    //TODO 
    mode = Mode::NORMAL;
}

void Editor::event_search(ftxui::Event e) {
    //TODO
    mode = Mode::NORMAL;
}

Editor::Mode Editor::get_mode() const {return mode;}
std::string Editor::command() const {return command_buffer;}
    
void Editor::move_left() {cursor.move(-1);}
void Editor::move_right() {cursor.move(1);}
void Editor::move_up() {cursor.move(-bytes_per_row * 2);}
void Editor::move_down() {cursor.move(bytes_per_row * 2);}

void Editor::execute_command() {
    if (command_buffer == "q") {quit();}
    if (command_buffer == "w") {save();}
    if (command_buffer == "wq") {save(); quit();}
}

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

void Editor::save() {
    buffer.save();
}

void Editor::quit() {
    if (!buffer.status()) {return;}
}

Editor::Editor(core::Buffer &buffer_,
               core::Cursor &cursor_,
               size_t bytes_per_row_)
    : buffer(buffer_),
      cursor(cursor_),
      bytes_per_row(bytes_per_row_),
      has_pending(false),
      pending(0),
      command_buffer(""),
      mode(Mode::NORMAL) {}
}
