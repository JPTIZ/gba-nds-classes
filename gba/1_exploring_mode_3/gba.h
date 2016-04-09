#ifndef GBA_H
#define GBA_H

#include <cstdint>

namespace gba {
namespace video {

enum LCDControl {
    GBA_BIT = 1<<3,
    HBLANK_OAM_ACCESS = 1<<5,
    OBJ2D = 1<<6,
    FORCE_BLANK = 1<<7,
    OBJ_LAYER = 1<<0xC,
}

inline auto& lcd_control() {
    return *reinterpret_cast<std::uint16_t*>(0x4000000);
}

void enable_bg(unsigned layer) {
    lcd_control() |= 1 << (layer+8);
}

}
}
