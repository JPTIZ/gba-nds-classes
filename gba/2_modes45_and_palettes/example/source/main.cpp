#include "gba.h"
#include "video_operations.h"

int main() {
    {
        using namespace gba::video;
        lcd_control() = 5;
        enable_bg(2);
    }
    for (auto i = 0u; i < 160*128; ++i) {
        gba::video::vram()[i] = 0x1F;
    }
    for (auto i = 0u; i < 160*128; ++i) {
        gba::video::vram()[i+160*128] = 0x1F<<5;
    }
    while (true) {
        gba::video::vsync();
        gba::video::flip_pages();
    }
}
