#ifndef GBA_GEOMETRY_H
#define GBA_GEOMETRY_H

#include <cstdint>

namespace gba {
namespace geometry {

struct Point {
    std::int16_t x, y;
};

struct Rect {
    std::int16_t x, y, width, height;
    auto right() const {
        return x + width;
    }

    auto bottom() const {
        return y + height;
    }
};

}
}

#endif
