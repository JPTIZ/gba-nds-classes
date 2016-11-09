#include "mode4.h"

#include "gba_video.h"

namespace gba {
namespace video {

void mode4::draw_horizontal_line(
        uint16_t x, uint16_t y, uint16_t width, uint16_t data)
{
    auto x2 = x + (width/2);
    if (x % 2 != 0) {
        vram()[x + SCREEN_WIDTH*y] = data>>8;
    }
    for (; x < x2; ++x) {
        vram()[x + SCREEN_WIDTH*y] = data;
    }
    if (width % 2 != 0) {
        vram()[x + SCREEN_WIDTH*y] = data & 0xff00;
    }
}

void mode4::draw_vertical_line(
        uint16_t x, uint16_t y, uint16_t height, uint16_t data)
{
    auto y2 = y + height;
    if (x % 2 != 0) {
        data = data & 0xff00;
    } else {
        data = data & 0x00ff;
    }
    for (; y < y2; ++y) {
        vram()[x + SCREEN_WIDTH*y] = data;
    }
}

void mode4::draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t data) {
    //width /= 2;
    draw_vertical_line(x, y + 1, height - 2, data);
    draw_vertical_line(x + width - 1, y + 1, height - 2, data);
    draw_horizontal_line(x, y, width, data);
    draw_horizontal_line(x, y + height - 1, width, data);
}

}
}

