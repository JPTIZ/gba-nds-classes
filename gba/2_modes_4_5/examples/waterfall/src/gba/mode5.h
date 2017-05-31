#ifndef GBA_MODE5_H
#define GBA_MODE5_H

#include <cstdint>

#include "io.h"

namespace gba::video::mode5 {

/**
 * Acessa a memória de vídeo nas coordenadas (x, y)
 */
std::uint16_t& vram(unsigned x, unsigned y);

void fill_screen(std::uint16_t color);
void vsync();

/**
 * Alterna entre as páginas de exibição
 */
void page_flip();

}

#endif
