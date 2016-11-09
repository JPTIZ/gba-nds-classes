#include "gba/gba_video.h"
#include "gba/mode4.h"

int main() {
    using namespace gba;
    {
        using namespace video;
        video::control_register() = 0;
        ((unsigned short*)0x5000000)[0x1] = 0x1F;
        ((unsigned short*)0x5000000)[0x2] = 0x1F<<5;
        ((unsigned short*)0x5000000)[0x3] = 0x1F<<10;
        set_mode(4);
        enable_bg(2);
    }
    {
        namespace mode = gba::video::mode4;
        mode::draw_horizontal_line(11, 20, 10, 0x101);
        mode::draw_rect(0, 0, 5, 5, 0x101);
        mode::draw_rect(1, 1, 3, 3, 0x202);
        mode::draw_rect(2, 2, 1, 1, 0x303);
    }
    while (true) {}
    return 0;
}
