#ifndef GBA_H
#define GBA_H

#include <cstdint>

namespace gba {
namespace video {

// Note: added
enum LCDControl {
    HBLANK_OAM_ACCESS = 1<<5,
    OBJ2D = 1<<6,
    FORCE_BLANK = 1<<7,
    OBJ_LAYER = 1<<0xC,
};

inline auto& lcd_control() {
    return *reinterpret_cast<std::uint16_t*>(0x4000000);
}

inline void enable_bg(unsigned layer) {
    lcd_control() |= 1 << (layer+8);
}

inline auto vram() {
    return reinterpret_cast<std::uint16_t*>(0x6000000);
}

inline void vram(std::uint8_t x, std::uint8_t y, std::uint16_t data) {
    vram()[x + 240*y] = data;
}

struct Color {
    std::uint16_t value;

    Color(std::uint16_t value): value{value} {}

    Color(std::uint8_t r, std::uint8_t g, std::uint8_t b):
        value(r + (g<<5) + (b<<10)) {}

    std::uint8_t r() {
        return value & 0x1F;
    }

    std::uint8_t g() {
        return (value>>5) & 0x1F;
    }

    std::uint8_t b() {
        return (value>>10) & 0x1F;
    }
};

}
}

#endif
