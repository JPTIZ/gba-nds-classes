#include "gba_video.h"

namespace gba {

uint16_t& video::control_register() {
    return *reinterpret_cast<uint16_t*>(0x4000000);
}

void video::enable_bg(uint8_t layer) {
    control_register() |= 1 << (layer+8);
}

void video::set_mode(uint8_t mode) {
    control_register() = (control_register() & 0xFFF8) | mode;
}

volatile uint16_t* video::vram() {
    return reinterpret_cast<uint16_t*>(0x6000000);
}

}
