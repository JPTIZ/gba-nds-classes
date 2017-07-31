#ifndef GBA_VIDEO_H
#define GBA_VIDEO_H

#include <bitset>
#include <cstdint>

#include "utility.h"
#include "graphics.h"

namespace gba::video {

static auto& lcd_control = *new (reinterpret_cast<void*>(0x0400'0000)) std::bitset<16>();

enum LCDControl {
    PAGE = 1 << 4,
    OAM_ON_HBLANK = 1 << 5,
    OBJ_MAPPING = 1 << 6,
    FORCE_BLANK = 1 << 7,
    BG0 = 1 << 8,
    BG1 = 1 << 9,
    BG2 = 1 << 10,
    BG3 = 1 << 11,
    OBJ = 1 << 12,
    WIN0 = 1 << 13,
    WIN1 = 1 << 14,
    OBJWIN1 = 1 << 15,
};

inline volatile auto& vcount() {
    return *reinterpret_cast<std::uint16_t*>(0x4000006);
}

inline volatile auto palette_ram() {
    return reinterpret_cast<std::uint16_t*>(0x5000000);
}

inline void vsync() {
    while (vcount() >= 160) {}
    while (vcount() < 160) {}
}

inline void bg_visible(graphics::Layer layer, bool enabled=true) {
    lcd_control[utils::value_of(layer)+8] = enabled;
}

inline void force_blank(bool force) {
    lcd_control[7] = force;
}

inline void set_mode(graphics::Mode mode) {
    lcd_control = (lcd_control.to_ulong() & (~0b111)) | utils::value_of(mode);
}

}

#endif
