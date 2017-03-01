#include "mode3.h"

#include "video.h"

using namespace gba::video;
using namespace gba::geometry;

void mode3::fill_rect(const Rect& rect, const Color& color) {
    for (auto y = rect.y; y < rect.bottom(); ++y) {
        for (auto x = rect.x; x < rect.right(); ++x) {
            (std::uint16_t&)vram({x, y}) = color.value;
        }
    }
}

