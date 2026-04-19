#include <view.hpp>

namespace render {

View::View() : size(0), line_hex(""), deq_hex(0) {};

std::string& View::get_string_hex(const std::deque<unsigned char> &data, size_t from, size_t to) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (size_t i = from; i < to; ++i) {
        oss << std::setw(2) << static_cast<int>(data[i]);
    }
    line_hex = oss.str();
    return line_hex;
}

std::deque<std::string>& View::get_deq_hex(const std::deque<unsigned char> &data, size_t from, size_t to) {
    deq_hex.clear();
    for (size_t i = from; i < to; ++i) {
        std::ostringstream oss;
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
        deq_hex.push_back(oss.str());
    }
    return deq_hex;
}
}
