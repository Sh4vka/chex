#pragma once
#include <cstddef>
#include <cstdint>

namespace core {

class Cursor {
public:
    size_t position() const;
    size_t byte() const;
    size_t get_max_position() const;
    uint8_t nibble_index() const;

    void set_max_position(const size_t max_position_);

    void move(const int val);

    Cursor();
    Cursor(const size_t max_position_);

private:
    size_t nibble;
    size_t max_position;
};
}
