#ifndef GBA_GRAPHICS_H
#define GBA_GRAPHICS_H

#include <cstdint>

#include "io.h"

namespace gba::video {

inline auto& lcd_control() {
    return *reinterpret_cast<std::uint16_t*>(0x4000000);
}

}

#endif
