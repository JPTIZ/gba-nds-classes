#ifndef GBA_VIDEO_H
#define GBA_VIDEO_H

#include "types.h"

namespace gba {
namespace video {

void enable_bg(uint8_t bg);
void set_mode(uint8_t mode);
uint16_t& control_register();
volatile uint16_t* vram();

}
}

#endif
