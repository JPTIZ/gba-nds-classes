#include "mode3.h"

namespace gba::video {

void mode3::fill_screen(std::uint16_t color) {
    for (auto y = 0u; y < 160u; ++y) {
        for (auto x = 0u; x < 240u; ++x) {
            vram(x, y) = color;
        }
    }
}

void mode3::vsync() {
    auto& scanline = *(volatile std::uint16_t*)0x4000006;
    while (scanline > 160u) {}
    while (scanline < 160u) {}
}

}
