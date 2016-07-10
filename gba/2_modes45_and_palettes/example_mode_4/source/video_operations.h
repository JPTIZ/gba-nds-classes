#ifndef GBA_VIDEO_OPERATIONS_H
#define GBA_VIDEO_OPERATIONS_H

#include "gba.h"

namespace gba {
namespace video {

void vsync();
void fill_screen(std::uint16_t data);
void clear_screen();
void flip_pages();

}
}

#endif
