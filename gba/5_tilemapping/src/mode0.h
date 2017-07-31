#ifndef GBA_MODE0_H
#define GBA_MODE0_H

#include <cstdint>
#include <array>

namespace gba::graphics::mode0 {

static auto& bg_palette = *new (reinterpret_cast<void*>(0x0500'0000)) std::array<std::uint16_t, 256>{};

}

#endif
