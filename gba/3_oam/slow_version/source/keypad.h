#ifndef GBA_KEYPAD_H
#define GBA_KEYPAD_H

#include <cstdint>

namespace gba {
namespace keypad {

enum Keypad {
    A = 1 << 0,
    B = 1 << 1,
    SELECT = 1 << 2,
    START = 1 << 3,
    RIGHT = 1 << 4,
    LEFT = 1 << 5,
    UP = 1 << 6,
    DOWN = 1 << 7,
    R = 1 << 8,
    L = 1 << 9,
};

inline const auto& keystatus_register() {
    return *reinterpret_cast<std::uint16_t*>(0x4000130);
}

inline auto pressed(const Keypad& key) {
    return not (keystatus_register() & key);
}

}
}

#endif
