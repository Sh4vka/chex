#include "cursor.hpp"

namespace core {

Cursor::Cursor() : position_(0), max_position_(0) {};

Cursor::Cursor(size_t max_position) : position_(0), max_position_(max_position) {};

void Cursor::set_max_position(const size_t &max_position) {max_position_ = max_position;}

void Cursor::set_position(const size_t &position) {position_ = position;}

int Cursor::move_left(size_t amount) {
    if (position_ <= amount) {
        position_ -= amount;
        return 0;
    }
    return 1;
}

int Cursor::move_right(size_t amount) {
    if (position_ + amount <= max_position_) {
        position_ += amount;
        return 0;
    }
    return 1;
}

size_t Cursor::get_position() const {return position_;}

size_t Cursor::get_max_position() const {return max_position_;}

}
