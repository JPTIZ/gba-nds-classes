#include "video_operations.h"

#include <algorithm>

std::uint16_t* page;

std::uint8_t gba::video::mode() {
    return gba::video::lcd_control();
}

auto gba::video::size() {
    switch (gba::video::mode()) {
        case 3:
        case 4:
            return gba::types::Size16{240, 160};
    }
    return gba::types::Size16{160, 128};
}

auto gba::video::width() {
    return reinterpret_cast<std::uint16_t>(size().width);
}

void gba::video::vsync() {
    volatile auto scancount_register = (std::uint16_t*)0x4000006;
    while (*scancount_register < 160) {}
    while (*scancount_register > 160) {}
}

void gba::video::fill_screen(std::uint16_t data) {
    gba::video::draw_rect(0u, 0u, 240u, 160u, 0u);
}

void gba::video::clear_screen() {
    fill_screen(0);
}

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
        if (dp < 0) {
            dp = dp + 2 * (++x) + 3;
        } else {
            dp = dp + 2 * (++x) - 2 * (--y) + 5;
        }
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

void gba::video::flip_pages() {
    using namespace gba::video;
    lcd_control() ^= LCDControl::PAGE_BIT;
    auto current_page = lcd_control() & LCDControl::PAGE_BIT;
    page = reinterpret_cast<std::uint16_t*>(0x6000000 + 0x3E8 * current_page);
}

