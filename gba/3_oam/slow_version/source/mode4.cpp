#include "mode4.h"

#include "video.h"

using namespace gba::video;
using namespace gba::geometry;

void mode4::fill_rect(const Rect& rect, const Color& color) {
    for (auto y = rect.y; y < rect.bottom(); ++y) {
        for (auto x = rect.x; x < rect.right(); ++x) {
            vram({x, y}) = color.value;
        }
    }
}
