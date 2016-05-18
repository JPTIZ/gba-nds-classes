#ifndef GBA_VIDEO_OPERATIONS_H
#define GBA_VIDEO_OPERATIONS_H

#include "gba.h"

namespace gba {
namespace video {

void fill_screen(std::uint16_t color);
void draw_data(std::uint8_t x, std::uint8_t y);

}
}

#endif
