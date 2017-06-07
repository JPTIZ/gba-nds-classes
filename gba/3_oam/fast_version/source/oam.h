#ifndef GBA_OAM_H
#define GBA_OAM_H

#include <cstdint>

#include "geometry.h"

namespace gba {
namespace video {
namespace oam {

using namespace geometry;

struct OAMEntry {
    std::uint16_t attribute0;
    std::uint16_t attribute1;
    std::uint16_t attribute2;
};

inline auto volatile sprite_ram() {
    return reinterpret_cast<std::uint16_t*>(0x6010000);
}

inline auto volatile sprite_palette_ram() {
    return reinterpret_cast<std::uint16_t*>(0x5000200);
}

inline auto* oam() {
    return reinterpret_cast<OAMEntry*>(0x7000000);
}

class Sprite {
public:
    Sprite(std::uint16_t* palette, std::uint16_t* data);
    void move(const Point&);
    void offset(const Point&);
    void rotate(std::int16_t angle);
    void flip_horizontally();
    void flip_vertically();

private:
    OAMEntry oam_entry;

};

}
}
}

#endif
