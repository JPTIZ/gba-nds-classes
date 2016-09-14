#include "gba.h"
#include "video_operations.h"

int main() {
    {
        using namespace gba::video;
        lcd_control() = 4;
        enable_bg(2);
    }

    gba::video::palette(1, 0x1F);
    gba::video::palette(2, 0x1F<<5);

    auto screen_size = 124u*160u;
    for (auto i = 0u; i < screen_size; ++i) {
        gba::video::vram()[i] = 0x0101;
    }
    for (auto i = 0u; i < screen_size; ++i) {
        gba::video::vram()[i+screen_size] = 0x0202;
    }
    while (true) {
        gba::video::vsync();
        gba::video::flip_pages();
    }
}
