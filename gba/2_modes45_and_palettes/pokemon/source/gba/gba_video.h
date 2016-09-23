#ifndef GBA_VIDEO_H
#define GBA_VIDEO_H

#include <cstdint>

namespace gba {
namespace video {

void enable_bg(std::uint8_t bg);
void set_mode(std::uint8_t mode);
std::uint16_t& control_register();
volatile std::uint16_t* vram();

}
}

#endif
