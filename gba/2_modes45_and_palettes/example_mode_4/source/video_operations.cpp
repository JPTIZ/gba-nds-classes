#include "video_operations.h"

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

void gba::video::draw_line(std::uint8_t x0, std::uint8_t y0, std::uint8_t x1, std::uint8_t y1, std::uint16_t color) {
    auto dx = x1 - x0;
    auto dy = y1 - y0;
    auto x_step = (signed)dx < 0 ? -1 : 1;
    auto y_step = (signed)dy < 0 ? -1 : 1;
    auto x = x0;
    auto y = y0;
    /*
     */
    while (x != x1 && y != y1) {
        if (dy > dx) {
            auto x_ = x0 + dx * (y - y0) / dy;
            auto next_x = x0 + dx * (y + y_step - y0) / dy;
            //auto next_x = x_ + x_step;
            while (x != next_x) {
                gba::video::vram(x_, y, color);
                x += x_step;
            }
            y += y_step;
        } else {
            auto y_ = y0 + dy * (x - x0) / dx;
            auto next_y = y0 + dy * (x + x_step - x0) / dx;
            //auto next_y = y_ + y_step;
            while (y != next_y) {
                gba::video::vram(x, y_, color);
                y += y_step;
            }
            x += x_step;
        }
    }
    return;
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

std::uint16_t* page;

void gba::video::flip_pages() {
    using namespace gba::video;
    lcd_control() ^= LCDControl::PAGE_BIT;
    auto current_page = lcd_control() & LCDControl::PAGE_BIT;
    page = reinterpret_cast<std::uint16_t*>(0x6000000 + 0x3E8 * current_page);
}

