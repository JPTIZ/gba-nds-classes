#include "mode4.h"
#include "oam.h"
#include "keypad.h"
#include "resources/link.h"

template <typename T, typename U>
auto min(const T& a, const U& b) {
    return a < b ? a : b;
}

template <typename T, typename U>
auto max(const T& a, const U& b) {
    return a > b ? a : b;
}

void draw_link(const gba::geometry::Point& position) {
    using namespace gba::resources;
    using namespace gba::video::mode4;
    for (auto y = std::int16_t{0}; y < 24; ++y) {
        for (auto x = std::int16_t{0}; x < 12; ++x) {
            auto x_ = (short)(x + position.x);
            auto y_ = (short)(y + position.y);
            vram({x_, y_}) = link_data[x + 12 * y];
        }
    }
}

void move_link_to(const gba::geometry::Point& destiny) {
    using namespace gba::video::oam;
    auto& entry = *reinterpret_cast<OAMEntry*>(oam());
    //                   FEDCBA9876543210
    entry.attribute0 = 0b0010000000000000 | std::int8_t(destiny.y);
    entry.attribute1 = 0b1000000000000000 | std::int8_t(destiny.x);
    entry.attribute2 = 0b0000000000000000 | 0;
}

void send_link_to_oam() {
    using namespace gba::resources;
    using namespace gba::video::oam;

    for (auto i = 1; i < 14; ++i) {
        sprite_palette_ram()[i] = link_palette[i];
    }

    for (auto y = std::int16_t{0}; y < 24; ++y) {
        for (auto x = std::int16_t{0}; x < 12; ++x) {
            sprite_ram()[x + 16 * y] = 0;
        }
    }

    for (auto y = std::int16_t{0}; y < 24; ++y) {
        for (auto x = std::int16_t{0}; x < 12; ++x) {
            sprite_ram()[x + 16 * y] = link_data[x + 12 * y];
        }
    }

    /*auto text = "ARQUITETURA\nFODA";
    for (auto i = 0; i < 17; ++i) {
        sprite_ram()[i] = text[i];
    }
    */

    move_link_to({32, 16});
}

int main() {
    using namespace gba::resources;
    using namespace gba::video;
    using namespace gba::video::mode4;
    using namespace gba::video::oam;

    flip_page();

    {
        using gba::video::LCDControl;
        lcd_control() = (LCDControl::BG2 | LCDControl::OBJ | LCDControl::OBJ_MAPPING) + 4;
    }

    for (auto i = 1; i < 14; ++i) {
        palette_ram()[i] = link_palette[i];
    }

    send_link_to_oam();

    auto link_x = short{0};
    auto link_y = short{0};
    while (true) {
        using namespace gba::keypad;

        vsync();
        //fill_rect({0, 0, screen_width()>>1, screen_height()}, {0});

        if (pressed(Keypad::LEFT)) {
            --link_x;
        }
        if (pressed(Keypad::RIGHT)) {
            ++link_x;
        }
        if (pressed(Keypad::UP)) {
            --link_y;
        }
        if (pressed(Keypad::DOWN)) {
            ++link_y;
        }
        if (pressed(Keypad::R)) {
            link_x = 0;
            link_y = 0;
        }

        link_x = max(0, min((screen_width()>>1) - 12, link_x));
        link_y = max(0, min(screen_height() - 24, link_y));

        move_link_to({link_x, link_y});
        draw_link({link_x, link_y});

        //flip_page();
    }
}
