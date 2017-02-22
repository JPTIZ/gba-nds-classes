#ifndef GBA_VIDEO_H
#define GBA_VIDEO_H

#include <cstdint>

namespace gba::video {

inline auto& lcd_control() {
    return *reinterpret_cast<std::uint16_t*>(0x4000000);
}

inline volatile auto& vcount() {
    return *reinterpret_cast<std::uint16_t*>(0x4000006);
}

inline void vsync() {
    while (vcount() >= 160) {}
    while (vcount() < 160) {}
}

}

#endif
