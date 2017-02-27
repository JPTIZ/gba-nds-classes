#include "mode4.h"
#include "keypad.h"
#include "resources/zelda.h"

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
            vram({x_, y_}) = zelda_data[x + 12 * y];
        }
    }
}

int main() {
    using namespace gba::resources;
    using namespace gba::video;
    using namespace gba::video::mode4;
    lcd_control() = gba::video::LCDControl::BG2 + 4;

    for (auto i = 1; i < 14; ++i) {
        palette_ram()[i] = zelda_palette[i];
    }

    auto link_x = short{0};
    auto link_y = short{0};
    while (true) {
        using namespace gba::keypad;
        fill_rect({0, 0, screen_width()>>1, screen_height()}, {0});
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
        draw_link({link_x, link_y});
    }
}
