#ifndef GBA_VIDEO_H
#define GBA_VIDEO_H

#include <cstdint>

namespace gba {
namespace video {

void enable_bg(std::uint8_t bg);

inline auto& control_register() {
    return *reinterpret_cast<std::uint16_t*>(0x6000000);
}

}
}

#endif
