#ifndef GBA_GEOMETRY_H
#define GBA_GEOMETRY_H

#include <cstdint>
#include "gba.h"

namespace gba {
namespace video {

void draw_rect(std::uint8_t x0, std::uint8_t y0, std::uint8_t width, std::uint8_t height, std::uint16_t color);
void draw_rect(std::uint8_t x0, std::uint8_t y0, std::uint8_t width, std::uint8_t height, Color color);
void draw_line(std::uint8_t x0, std::uint8_t y0, std::uint8_t x1, std::uint8_t y1, std::uint16_t color);
void draw_circle(std::uint8_t x0, std::uint8_t y0, std::uint8_t radius, std::uint16_t color);

}
}

#endif
