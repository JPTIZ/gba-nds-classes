#include <cstdint>
#include "gba.h"

int main() {
    {
        using namespace gba::video;
        // Sets mode 3
        lcd_control() = 3;
        enable_bg(2);
    }
    for (auto i = 0u; i < 160u; ++i) {
        gba::video::vram(i, i, 0x00FF);
    }
    while (1);
}
