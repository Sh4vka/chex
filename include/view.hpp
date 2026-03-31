#include <string>
#include <deque>
#include <sstream>
#include <iomanip>

namespace render {
class View {
public:
    std::string get_string_hex(const std::deque<unsigned char> &data, size_t from, size_t to);

private:
};
}
