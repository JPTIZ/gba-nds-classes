#include "geometry.h"

#include <algorithm>

#include "video_operations.h"

void gba::video::draw_rect(std::uint8_t x0, std::uint8_t y0, std::uint8_t width, std::uint8_t height, std::uint16_t color) {
    auto x1 = x0 + width;
    auto y1 = y0 + height;
    for (auto y = y0; y < y1; ++y) {
        for (auto x = x0; x < x1; ++x) {
            gba::video::vram(x, y, color);
        }
    }
}

void gba::video::draw_rect(std::uint8_t x0, std::uint8_t y0, std::uint8_t width, std::uint8_t height, Color color) {
    draw_rect(x0, y0, width, height, color.value);
}

void gba::video::draw_line(
        std::uint8_t x0, std::uint8_t y0,
        std::uint8_t x1, std::uint8_t y1,
        std::uint16_t color) {
    using std::swap;

    auto steep = std::abs(x0 - x1) < std::abs(y0 - y1);
    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
    }

    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    auto dx = x1 - x0;
    auto dy = y1 - y0;
    auto derror = std::abs(dy)*2;
    auto error = 0;
    auto y = y0;

    for (auto x = x0; x <= x1; ++x) {
        if (steep) {
            gba::video::vram(y, x, color);
        } else {
            gba::video::vram(x, y, color);
        }

        error += derror;

        if (error > dx) {
            y += (y1 > y0 ? 1 : -1);
            error -= dx*2;
        }
    }
}

void gba::video::draw_circle(std::uint8_t x0, std::uint8_t y0, std::uint8_t radius, std::uint16_t color) {
    int x = 0, y = radius;
    int dp = 1 - radius;
    do
    {
            if (dp < 0)
                    dp = dp + 2 * (++x) + 3;
            else
                    dp = dp + 2 * (++x) - 2 * (--y) + 5;

            gba::video::vram(x0 + x, y0 + y, 15);     //For the 8 octants
            gba::video::vram(x0 - x, y0 + y, 15);
            gba::video::vram(x0 + x, y0 - y, 15);
            gba::video::vram(x0 - x, y0 - y, 15);
            gba::video::vram(x0 + y, y0 + x, 15);
            gba::video::vram(x0 - y, y0 + x, 15);
            gba::video::vram(x0 + y, y0 - x, 15);
            gba::video::vram(x0 - y, y0 - x, 15);

    } while (x < y);
}


