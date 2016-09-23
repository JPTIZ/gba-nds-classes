#ifndef GBA_MODE4_H
#define GBA_MODE4_H

#include <cstdint>

namespace gba {
namespace video {
namespace mode4 {

const auto SCREEN_WIDTH = 120;
const auto SCREEN_HEIGHT = 160;

void draw_horizontal_line(
        std::uint16_t x, std::uint16_t y,
        std::uint16_t width, std::uint8_t data);
void draw_rect(std::uint16_t x, std::uint16_t y, std::uint16_t width, std::uint16_t height);

}
}
}

#endif
