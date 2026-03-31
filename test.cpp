#include <iostream>
#include "buffer.hpp"
#include "cursor.hpp"
#include "view.hpp"

int main() {
    std::string file = "test.bin";
    core::Buffer buf(file);
    core::Cursor cur(buf.size());
    buf.insert_byte('f', cur.get_position());
    render::View view;
    std::cout << view.get_string_hex(buf.get_data(), 0, buf.size()) << std::endl;
    return 0;
}
