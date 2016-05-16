#include <cstdint>
#include "gba.h"

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

int main() {
    {
        using namespace gba::video;
        // Sets mode 3
        lcd_control() = 3;
        enable_bg(2);
    }
    auto first_y = false;
    volatile auto color = first_y ? 1<<10u : 1;
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
