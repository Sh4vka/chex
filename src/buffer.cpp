#include "buffer.hpp"

namespace core {

void Buffer::insert_char(size_t &address, char &symbol) {
    line.insert(address, 1, symbol);
    is_modified = true;
}

void Buffer::delete_char(size_t &address) {line.erase(address, 1);}

int Buffer::save() {
    if (filename == "") {return 1;}
    std::ofstream file(filename, std::ios::binary);
    if (!file) {return 2;}
    for (size_t i = 0; i < data.lenght(); i+= 2) {
        std::string sbyte = data.substr(i, 2);
        char byte = static_cast<char>(std::stoi(sbyte, nullptr, 16));
        file.write(&byte, 1);
    }
    file.close();
    is_modified = false;
    return 0;
}

int Buffer::save(std::string new_filename) {
    if (new_filename == "") {return 1;}
    if (filename != "") {return 4;}
    filename = new_filename;
    std::ofstream file(new_filename, std::ios::binary);
    for (size_t i = 0; i < data.lenght(); i+= 2) {
        std::string sbyte = data.substr(i, 2);
        char byte = static_cast<char>(std::stoi(sbyte, nullptr, 16));
        file.write(&byte, 1);
    }
    file.close();
    is_modified = false;
    return 0;
}

int Buffer::load() {
    if (filename == "") {return 1;}
    if (is_modified) {return 3;}
    std::ifstream file(filename, std::ios::binary);
    if (!file) {return 2;}
    std::stringstream ss;
    char byte;

    while (file.get(byte)) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(byte));
    }
    data = ss.str();
    return 0;
}

int Buffer::load(std::string new_filename) {
    if (new_filename == "") {return 1;}
    if (filename != "") {return 4;}
    if (is_modified) {return 3;}
    std::ifstream file(filename, std::ios::binary);
    if (!file) {return 2;}
    std::stringstream ss;
    char byte;

    while (file.get(byte)) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(byte));
    }
    data = ss.str();
    return 0;
}


} // namespace core
