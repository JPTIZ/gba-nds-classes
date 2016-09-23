#include "mode4.h"

#include "gba_video.h"

namespace gba::video {

void mode4::draw_horizontal_line(
        std::uint16_t x, std::uint16_t y, std::uint16_t width, std::uint8_t data)
{
    auto data16 = data | (data<<8);
    auto x2 = x + width;
    for (; x <= x2; ++x) {
        vram()[x + SCREEN_WIDTH*y] = data16;
    }
}

void mode4::draw_rect(std::uint16_t x, std::uint16_t y, std::uint16_t width, std::uint16_t height) {
}

}

