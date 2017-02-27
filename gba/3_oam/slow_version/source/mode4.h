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

inline auto vram() {
    return reinterpret_cast<std::uint16_t*>(0x6000000);
}

inline auto& vram(const Point& point) {
    return vram()[point.x + (screen_width()>>1) * point.y];
}

void fill_rect(const Rect&, const Color&);

}
}
}

#endif
