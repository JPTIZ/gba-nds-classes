#ifndef GBA_MODE4_H
#define GBA_MODE4_H

#include "types.h"

namespace gba {
namespace video {
namespace mode4 {

const auto SCREEN_WIDTH = 120;
const auto SCREEN_HEIGHT = 160;

void draw_vertical_line(uint16_t x, uint16_t y, uint16_t width, uint16_t data);
void draw_horizontal_line(uint16_t x, uint16_t y, uint16_t width, uint16_t data);
void draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t data);

}
}
}

#endif
