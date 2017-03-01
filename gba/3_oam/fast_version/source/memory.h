#ifndef GBA_MEMORY_H
#define GBA_MEMORY_H

namespace gba {
namespace memory {

inline auto dram() {
    return reinterpret_cast<std::uint8_t*>(0x2000000);
}

inline auto sram() {
    return reinterpret_cast<std::uint8_t*>(0x3000000);
}

}
}

#endif
