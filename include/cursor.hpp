namespace core {

class Cursor {
public:
    void set_max_position(const size_t &max_position);
    void set_position(const size_t &position);

    int move_left(size_t amount = 1);
    int move_right(size_t amount = 1);

    size_t get_position() const;
    size_t get_max_position() const;

    Cursor();
    Cursor(size_t max_position);

private:
    size_t position_;
    size_t max_position_;
};
}
