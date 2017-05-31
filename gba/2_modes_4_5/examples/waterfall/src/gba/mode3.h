#ifndef GBA_MODE3_H
#define GBA_MODE3_H

#include <cstdint>

#include "io.h"

namespace gba::video::mode3 {

/**
 * Acessa a memória de vídeo nas coordenadas (x, y)
 */
inline auto& vram(unsigned x, unsigned y) {
    return io::register_at(0x6000000)[x + 240 * y];
}

void fill_screen(std::uint16_t color);
void vsync();

}

#endif
