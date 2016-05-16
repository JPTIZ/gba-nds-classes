#include "video_operations.h"

void gba::video::fill_screen(std::uint16_t data) {
    for (auto y = 0u; y < 160; ++y) {
        for (auto x = 0u; x < 240; ++x) {
            gba::video::vram(x, y, data);
        }
    }
}
