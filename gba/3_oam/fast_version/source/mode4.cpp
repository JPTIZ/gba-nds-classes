#include "mode4.h"

#include "video.h"

using namespace gba::video;
using namespace gba::geometry;

namespace {

auto page = reinterpret_cast<std::uint16_t*>(0x6000000);

}

std::uint16_t* mode4::vram() {
    return reinterpret_cast<std::uint16_t*>(page);
}

std::uint16_t& mode4::vram(const Point& point) {
    return vram()[point.x + (screen_width()>>1) * point.y];
}

void mode4::fill_rect(const Rect& rect, const Color& color) {
    for (auto y = rect.y; y < rect.bottom(); ++y) {
        for (auto x = rect.x; x < rect.right(); ++x) {
            vram({x, y}) = color.value;
        }
    }
}

void mode4::flip_page() {
    lcd_control() ^= LCDControl::PAGE;
    auto page_ = lcd_control() & LCDControl::PAGE;
    page = reinterpret_cast<std::uint16_t*>(0x6000000 + 0xA00 * page_);
}
