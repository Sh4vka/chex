#include "cursor.hpp"

namespace core {

template <class Buffer>
int Cursor::move_left(Buffer &buffer) {
    if (position == 0) {return 1;}
    if (line_position == 0) {
        position--;
        line--;
        line_position=max_line;
        return 0;
    }
    position--;
    line_position--;
    return 0;
}

template <class Buffer>
int Cursor::move_left(Buffer &buffer) {
    if (position + 1 >= buffer.size()) {return 1;}
    position++;
}
}
