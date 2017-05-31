#include "mode5.h"

#include "graphics.h"

namespace {

auto vram_base = gba::io::register_at(0x6000000);

}

namespace gba::video {

void mode5::page_flip() {
  lcd_control() ^= 0b10000;
  auto page_bit = (lcd_control() & 0b10000) >> 4;
  vram_base = io::register_at(0x6000000) + 160*128 * page_bit;
}

std::uint16_t& mode5::vram(unsigned x, unsigned y) {
     return vram_base[x + 160 * y];
}

void mode5::fill_screen(std::uint16_t color) {
    for (auto y = 0u; y < 128u; ++y) {
        for (auto x = 0u; x < 160u; ++x) {
            vram(x, y) = color;
        }
    }
}

void mode5::vsync() {
    auto& scanline = *(volatile std::uint16_t*)0x4000006;
    while (scanline > 128u) {}
    while (scanline < 128u) {}
}

}
