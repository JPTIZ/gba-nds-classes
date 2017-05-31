#include <cstdint>

#include "graphics.h"
#include "mode5.h"

int main() {
    using namespace gba::video;

    auto lcd_control = (std::uint16_t*)0x4000000;
    *lcd_control = 0x405;

    auto bla = 1;
    while (true) {
        mode5::fill_screen(0b11111 << (bla * 10));
        vsync();
        page_flip();
        bla ^= 1;
    }
}
