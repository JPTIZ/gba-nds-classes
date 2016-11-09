#include "video_operations.h"
#include "geometry.h"

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

std::uint16_t* page;

void gba::video::flip_pages() {
    using namespace gba::video;
    lcd_control() ^= LCDControl::PAGE_BIT;
    auto current_page = lcd_control() & LCDControl::PAGE_BIT;
    page = reinterpret_cast<std::uint16_t*>(0x6000000 + 0x3E8 * current_page);
}

