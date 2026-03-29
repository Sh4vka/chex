namespace core {

template <class Buffer>
class Cursor {
public:
    Cursor() : position(0), line(0), line_position(0), max_line(1) {};
    Cursor(size_t &size_line) : position(0), line(0), line_position(0), max_line(size_line) {};

    void change_len_size(size_t size);

    int move_left(Buffer &buffer);
    int move_right(Buffer &buffer);
    int move_up(Buffer &buffer);
    int move_down(Buffer &buffer);

private:
    size_t position;
    size_t line;
    size_t line_position;
    size_t max_line;
};
}
