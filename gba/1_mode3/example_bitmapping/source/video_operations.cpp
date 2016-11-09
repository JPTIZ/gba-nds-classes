#include "video_operations.h"

void gba::video::fill_screen(std::uint16_t data) {
    for (auto y = 0u; y < 160; ++y) {
        for (auto x = 0u; x < 240; ++x) {
            gba::video::vram(x, y, data);
        }
    }
}

void gba::video::draw_data(std::uint8_t x, std::uint8_t y) {
    auto data_width = data.size()/7;
    for (auto i = 0u; i < data.size(); ++i) {
        // skip data if value is 0 (i.e. black = transparent)
        if (data[i] == 0) continue;
        gba::video::vram(
                x + i % data_width,
                x + i / data_width,
                data[i]);
    }
}
