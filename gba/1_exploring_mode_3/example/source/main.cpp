#include <cstdint>
#include <algorithm>
#include "gba.h"

void v_sync() {
    volatile auto scancount_register = (std::uint16_t*)0x4000006;
    while (*scancount_register < 160) {}
    while (*scancount_register > 160) {}
}

void wait() {
    for (volatile auto j = 0u; j < 65535;) {
        ++j;
    };
}

void clear_screen() {
    // clears screen
    for (auto j = 0u; j < 240u; ++j) {
        for (auto i = 0u; i < 160u; ++i) {
            gba::video::vram(j, i, 0);
        }
    }
}

void draw_line(std::uint8_t x0, std::uint8_t y0, std::uint8_t x1, std::uint8_t y1, std::uint16_t color) {
    auto dx = x1 - x0;
    auto dy = y1 - y0;
    auto D = dy - dx;
    auto y = y0;
    for (auto x = x0; x < x1-1; ++x) {
        gba::video::vram(x, y, color);
        if (D >= 0) {
            ++y;
            D -= dx;
        } else {
            D += dy;
        }
    }
    /*
    if (dx > dy) {
        for (auto y = y0; y < y1; ++y) {
            auto x = x0 + dx * (y - y0) / dy;
            auto next_x = x0 + dx * (y + 1 - y0) / dy;
            for (auto x_ = x; x_ < next_x; ++x_) {
                gba::video::vram(x_, y, color);
            }
        }
    } else {
        for (auto x = x0; x < x1; ++x) {
            auto y = y0 + dy * (x - x0) / dx;
            auto next_y = y0 + dy * (x + 1 - x0) / dx;
            for (auto y_ = y; y_ < next_y; ++y_) {
                gba::video::vram(x, y_, color);
            }
        }
    }
    */
}

void draw_circle(std::uint8_t x0, std::uint8_t y0, std::uint8_t radius, std::uint16_t color) {
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

int main() {
    {
        using namespace gba::video;
        // Sets mode 3
        lcd_control() = 3;
        enable_bg(2);
    }
    auto first_y = false;
    volatile auto color = first_y ? 1<<10u : 1;
    auto x = 160u;
    auto y = 100u;
    while (true) {
        v_sync();
        draw_line(120, 80, x, y, 0);
        if (*(std::uint16_t*)0x4000130 & (1<<4)) --x;
        if (*(std::uint16_t*)0x4000130 & (1<<5)) ++x;
        if (*(std::uint16_t*)0x4000130 & (1<<6)) ++y;
        if (*(std::uint16_t*)0x4000130 & (1<<7)) --y;

        draw_line(120, 80, x, y, 0x1F);
        gba::video::vram(x, y, 0x7FFF);
        draw_circle(120, 80, 70, 10);
    }
    while (1) {
        if (first_y) {
            // fills screen nicely
            for (auto i = 0u; i < 160u; ++i) {
                for (auto j = 0u; j < 240u; ++j) {
                    gba::video::vram(j, i, color);
                }
            }
            wait();
        } else {
            // fills screen badly
            for (auto j = 0u; j < 240u; ++j) {
                for (auto i = 0u; i < 160u; ++i) {
                    gba::video::vram(j, i, color);
                }
            }
            wait();
        }
        wait();
        if (color > (first_y ? 0x1F<<10u : 0x1F)) {
            color = (first_y ? 1<<10u : 1);
        }
        color += (first_y ? 1<<10u : 1);
    }
}
