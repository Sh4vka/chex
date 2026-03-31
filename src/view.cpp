#include "view.hpp"

namespace render {

std::string View::get_string_hex(const std::deque<unsigned char> &data, size_t from, size_t to) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (size_t i = from; i < to; ++i) {
        oss << std::setw(2) << static_cast<int>(data[i]);
    }
    return oss.str();
}
}
