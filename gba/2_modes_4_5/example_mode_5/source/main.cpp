#include "gba.h"
#include "video_operations.h"

int main() {
    {
        using namespace gba::video;
        lcd_control() = 5;
        enable_bg(2);
    }
    /*
    for (auto i = 0u; i < 160*128; ++i) {
        gba::video::vram()[i] = 0x1F;
    }
    for (auto i = 0u; i < 160*128; ++i) {
        gba::video::vram()[i+160*128] = 0x1F<<5;
    }*/
    auto x = 0u;
    auto y = 0u;
    auto color = gba::video::Color{0, 31, 0}.value;
    while (true) {
        gba::video::vsync();
        gba::video::clear_screen();
        gba::video::draw_circle(x, y, 5, color);
        gba::video::flip_pages();
    }
}
