#include <cursor.hpp>

namespace core {

Cursor::Cursor() : nibble(0), max_position(0){};

Cursor::Cursor(const size_t max_position) : nibble(0), max_position(max_position) {};

size_t Cursor::byte() const {return nibble / 2;}
size_t Cursor::position() const {return nibble;}
size_t Cursor::get_max_position() const {return max_position;}
uint8_t Cursor::nibble_index() const {return nibble % 2;}

void Cursor::move(const int val) {
    if (val < 0) {
        size_t amount = static_cast<size_t>(-val);
        if (nibble >= amount) {nibble -= amount;}
        else {nibble = 0;}
    } else {
        size_t amount = static_cast<size_t>(val);
        if (nibble + amount <= max_position) {nibble += amount;}
        else {nibble = max_position;}
    }
}

void Cursor::set_max_position(const size_t max_position_) {max_position = max_position_;}

}
