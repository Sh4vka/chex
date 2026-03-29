#pragma once
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>

namespace core {

class Buffer {
public:
    bool check_modified() const {return is_modified;}

    void insert_char(size_t &address, char &symbol,);

    void delete_char(size_t &address);
    
    int save();
    int save(std::string &new_filename);

    int load();
    int load(std::string &new_filename);

    Buffer() : is_modified(false), filename("");
    Buffer(std::string &filename_) : data(""), is_modified(false), filename(filename_);
    
private:
    std::string data;
    bool is_modified;
    std::string filename;
};
} // namespace core
