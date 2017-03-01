#ifndef GBA_MODE3_H
#define GBA_MODE3_H

#include <cstdint>

#include "geometry.h"
#include "video.h"

namespace gba {
namespace video {
namespace mode3 {

using namespace geometry;

constexpr inline auto screen_width() {
    return 240;
}

constexpr inline auto screen_height() {
    return 160;
}

inline auto vram() {
    return reinterpret_cast<std::uint16_t*>(0x6000000);
}

inline auto& vram(const Point& point) {
    return vram()[point.x + screen_width() * point.y];
}

void fill_rect(const Rect&, const Color&);

}
}
}

#endif
