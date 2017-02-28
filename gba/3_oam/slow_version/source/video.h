#ifndef GBA_VIDEO_H
#define GBA_VIDEO_H

#include <cstdint>

namespace gba {
namespace video {

enum LCDControl {
    PAGE = 1 << 4,
    OAM_ON_HBLANK = 1 << 5,
    OBJ_MAPPING = 1 << 6,
    FORCE_BLANK = 1 << 7,
    BG0 = 1 << 8,
    BG1 = 1 << 9,
    BG2 = 1 << 10,
    BG3 = 1 << 11,
    OBJ_LAYER = 1 << 12,
    WIN0 = 1 << 13,
    WIN1 = 1 << 14,
    OBJWIN1 = 1 << 15,
};

inline auto& lcd_control() {
    return *reinterpret_cast<std::uint16_t*>(0x4000000);
}

inline volatile auto& vcount() {
    return *reinterpret_cast<std::uint16_t*>(0x4000006);
}

inline auto palette_ram() {
    return reinterpret_cast<std::uint16_t*>(0x5000000);
}

inline void vsync() {
    while (vcount() >= 160) {}
    while (vcount() < 160) {}
}

struct Color {
    std::uint16_t value;
};

}
}

#endif
