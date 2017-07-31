#include "video.h"
#include "mode0.h"

using namespace gba::video;
using namespace gba::graphics;

int main() {
    using mode0::bg_palette;
    force_blank(false);
    bg_visible(Layer::BG0);
    set_mode(Mode::MODE0);

    bg_palette[1] = 0x1f;
    bg_palette[2] = 0x1f << 5;
    bg_palette[3] = 0x1f << 10;
}
