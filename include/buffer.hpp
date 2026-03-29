#include <fstream>
#include <string>
#include <deque>

namespace core {

class Buffer {
public:
    int load(std::string &filename);

    int save();
    int save(std::string &filename);

    size_t size() const;
    bool status() const;
    std::deque<char> get_data() const;
    std::string get_filename() const;

    int insert_byte(const char &byte, const size_t &index);
    int erase_byte(const size_t &index);

    Buffer();
    Buffer(std::string &filename);

private:
    std::deque<char> data_;
    std::string filename_;
    bool is_modified;
};
}
