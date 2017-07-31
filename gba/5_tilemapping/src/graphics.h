#ifndef GBA_GRAPHICS_H
#define GBA_GRAPHICS_H

namespace gba::graphics {

enum class Mode {
    MODE0,
    MODE1,
    MODE2,
    MODE3,
    MODE4,
    MODE5,
};

enum class Layer {
    BG0,
    BG1,
    BG2,
    BG3,
    OBJ,
};

struct Color {
    std::uint16_t value;

    auto r() const {
        return value & 0x1f;
    }

    auto g() const {
        return (value >> 5) & 0x1f;
    }

    auto b() const {
        return (value >> 10) & 0x1f;
    }
};

}

#endif
