#ifndef GBA_MODE4_H
#define GBA_MODE4_H

#include <cstdint>

#include "geometry.h"

namespace gba::video::mode4 {

inline auto vram() {
    return reinterpret_cast<std::uint8_t*>(0x6000000);
}

inline auto vram(const Point& point) {
    return vram()[point.x + SCREEN_WIDTH * point.y];
}

inline void vram(const Point& point, std::uint8_t index) {
    vram()[point.x + SCREEN_WIDTH * point.y] = index;
}

}

#endif
