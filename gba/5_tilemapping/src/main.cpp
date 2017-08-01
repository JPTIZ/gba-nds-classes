#include "keypad.h"
#include "tiles.h"
#include "video.h"

using namespace gba::video;
using namespace gba::graphics;

struct Point {
    int x, y;
};

int main() {
    using namespace layers;
    using namespace gba::keypad;

    force_blank(false);
    bg_visible(Layer::BG0);
    bg_visible(Layer::BG1);
    set_mode(Mode::MODE0);

    bg_palette[1] = 0x1f;
    bg_palette[2] = 0x1f << 5;
    bg_palette[3] = 0x17 << 10;
    bg_palette[4] = bg_palette[1] | bg_palette[2];
    bg_palette[5] = bg_palette[2] | bg_palette[3];
    bg_palette[6] = bg_palette[1] | bg_palette[3];
    bg_palette[7] = 0xffff;

    tiles[1] = {0x33333333,
                0x33333333,
                0x33333333,
                0x33333333,
                0x33333333,
                0x33333333,
                0x33333333,
                0x33333333};

    tiles[2] = {0x11111111,
                0x12222222,
                0x12111111,
                0x12111111,
                0x12111111,
                0x12111111,
                0x12111122,
                0x12111121};

    tiles[3] = {0x11111111,
                0x22222222,
                0x11111111,
                0x11111111,
                0x11111111,
                0x11111111,
                0x22222222,
                0x11111111};

    tiles[4] = {0x11111111,
                0x22222221,
                0x11111121,
                0x11111121,
                0x11111121,
                0x11111121,
                0x22111121,
                0x12111121};

    tiles[5] = {0x12111121,
                0x12111122,
                0x12111111,
                0x12111111,
                0x12111111,
                0x12111111,
                0x12222222,
                0x11111111};

    tiles[6] = {0x12111121,
                0x22111121,
                0x11111121,
                0x11111121,
                0x11111121,
                0x11111121,
                0x22222221,
                0x11111111};

    tiles[7] = {0x12111121,
                0x12111121,
                0x12111121,
                0x12111121,
                0x12111121,
                0x12111121,
                0x12111121,
                0x12111121};

    for (auto x = 1; x < 31; ++x) {
        for (auto y = 1; y < 31; ++y) {
            tilemap[x + 32 * y] = 0x1;
        }
    }

    tilemap[4 + 32 * 4] = 0x4;
    tilemap[5 + 32 * 4] = 0x3;
    tilemap[6 + 32 * 4] = 0x3;
    tilemap[7 + 32 * 4] = 0x2;

    tilemap[4 + 32 * 5] = 0x7;
    tilemap[4 + 32 * 6] = 0x7;

    tilemap[7 + 32 * 5] = 0x7;
    tilemap[7 + 32 * 6] = 0x7;

    tilemap[4 + 32 * 7] = 0x6;
    tilemap[5 + 32 * 7] = 0x3;
    tilemap[6 + 32 * 7] = 0x3;
    tilemap[7 + 32 * 7] = 0x5;


    tilemap[6 + 32 * 6 + 0x400] = 0x4;
    tilemap[7 + 32 * 6 + 0x400] = 0x3;
    tilemap[8 + 32 * 6 + 0x400] = 0x3;
    tilemap[9 + 32 * 6 + 0x400] = 0x2;

    tilemap[6 + 32 * 7 + 0x400] = 0x7;
    tilemap[6 + 32 * 8 + 0x400] = 0x7;

    tilemap[9 + 32 * 7 + 0x400] = 0x7;
    tilemap[9 + 32 * 8 + 0x400] = 0x7;

    tilemap[6 + 32 * 9 + 0x400] = 0x6;
    tilemap[7 + 32 * 9 + 0x400] = 0x3;
    tilemap[8 + 32 * 9 + 0x400] = 0x3;
    tilemap[9 + 32 * 9 + 0x400] = 0x5;


    set_base_screenblock(Layer::BG0, 1);
    set_base_screenblock(Layer::BG1, 2);
    set_base_screenblock(Layer::BG2, 3);
    set_base_screenblock(Layer::BG3, 4);

    auto bg0_offset = Point{0, 0};
    auto bg0_priority = 0;

    while (true) {
        update_input();
        if (pressed(Keypad::DOWN)) {
            ++bg0_offset.y;
        }
        if (pressed(Keypad::UP)) {
            --bg0_offset.y;
        }
        if (pressed(Keypad::LEFT)) {
            --bg0_offset.x;
        }
        if (pressed(Keypad::RIGHT)) {
            ++bg0_offset.x;
        }
        set_bg_ox(Layer::BG0, bg0_offset.x);
        set_bg_oy(Layer::BG0, bg0_offset.y);

        if (triggered(Keypad::A)) {
            bg0_priority = (bg0_priority + 1) % 4;
            set_bg_priority(Layer::BG0, bg0_priority);
        }

        vsync();
    }
}
