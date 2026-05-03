#pragma once
#include <string>
#include <cstdint>
#include <deque>
#include <sstream>
#include <iomanip>

namespace render {
class View {
public:
    std::string& get_string_hex(const std::deque<unsigned char> &data, size_t from, size_t to);
    std::deque<std::string>& get_deq_hex(const std::deque<unsigned char> &data, size_t from, size_t to);
    
    View();
private:
    std::string line_hex;
    std::deque<std::string> deq_hex;
};
}
