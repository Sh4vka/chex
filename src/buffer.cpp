#include "buffer.hpp"

namespace core {

Buffer::Buffer() : filename_(""), is_modified(false) {};

Buffer::Buffer(std::string &filename) : filename_(filename), is_modified(false) {
    std::ifstream file(filename_, std::ios::binary | std::ios::ate);
    if (!file) {throw std::runtime_error("Open file");}
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    for (size_t i = 0; i < size; ++i) {
        char byte = 0;
        if (file.read(&byte, 1)) {data_.push_back(byte);}
    }
    file.close();
}

size_t Buffer::size() const {return data_.size();}

bool Buffer::status() const {return is_modified();}

std::deque<char> Buffer::get_data() const {return data_;}

std::string Buffer::get_filename() const {return filename_;}

int Buffer::load(std::string &filename) {
    if (is_modified) {return 1;}
    filename_ = filename;
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {return 2;}
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    for (size_t i = 0; i < size; i++) {
        char byte = 0;
        if (file.read(&byte, 1)) {data_.push_back(byte);}
    }
    file.close();
    return 0;
}

int save() {
    if (filename_.empty()) {return 1;}
    std::ofstream file(filename_, std::ios::binary);
    if (!file) {return 2;}
    for (size_t i = 0; i < data_.size(); ++i) {
        if (!file.write(&data_[i], 1)) {return 3;}
    }
    file.close();
    is_modified = false;
    return 0;
}

int save(std::string &filename) {
    if (!filename_.empty()) {return 1;}
    filename_ = filename;
    return save();
}

int insert_byte(const char &byte, const size_t &index) {
    if (data_.size() < index) {return 1};
    data_.insert(data_.begin() + index, byte);
    is_modified = true;
    return 0;
}

int erase_byte(const size_t &index) {
    if (index > data_.size()) {return 1;}
    data_.erase(data_.begin() + index);
    is_modified = true;
    return 0;
}

}
