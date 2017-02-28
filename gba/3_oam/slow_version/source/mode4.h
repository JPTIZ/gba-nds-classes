#ifndef GBA_MODE4_H
#define GBA_MODE4_H

#include <cstdint>

#include "geometry.h"
#include "video.h"

namespace gba {
namespace video {
namespace mode4 {

using namespace geometry;

constexpr inline auto screen_width() {
    return 240;
}

constexpr inline auto screen_height() {
    return 160;
}

std::uint16_t* vram();
std::uint16_t& vram(const Point& point);
void fill_rect(const Rect&, const Color&);
void flip_page();

}
}
}

#endif
