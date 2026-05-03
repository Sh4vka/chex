#pragma once 
namespace render {

struct Viewport {
    size_t offset = 0;
    size_t rows = 20;
    size_t bytes_per_row = 16;

    size_t visible_bytes() const {return rows * bytes_per_row;}
};

}
