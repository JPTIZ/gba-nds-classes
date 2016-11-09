#include <cstdint>
#include <algorithm>

#include "gba.h"
#include "video_operations.h"

void wait() {
    for (volatile auto j = 0u; j < 65535;) {
        ++j;
    };
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
    {
        auto x = 160u;
        auto y = 100u;
        while (true) {
            gba::video::v_sync();
            gba::video::draw_line(120, 80, x, y, 0);
            if (*(std::uint16_t*)0x4000130 & (1<<4)) --x;
            if (*(std::uint16_t*)0x4000130 & (1<<5)) ++x;
            if (*(std::uint16_t*)0x4000130 & (1<<6)) ++y;
            if (*(std::uint16_t*)0x4000130 & (1<<7)) --y;

            gba::video::draw_line(120, 80, x, y, 0x1F);
            gba::video::vram(x, y, 0x7FFF);
            gba::video::draw_circle(120, 80, 70, 10);
        }
    }

    while (1) {
        if (first_y) {
            // fills screen nicely
            for (auto y = 0u; y < 160u; ++y) {
                for (auto x = 0u; x < 240u; ++x) {
                    gba::video::vram(x, y, color);
                }
            }
            wait();
        } else {
            // fills screen badly (slower)
            for (auto x = 0u; x < 240u; ++x) {
                for (auto y = 0u; y < 160u; ++y) {
                    gba::video::vram(x, y, color);
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
