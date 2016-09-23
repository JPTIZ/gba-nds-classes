#include "gba/gba_video.h"
#include "gba/mode4.h"

int main() {
    using namespace gba;
    {
        using namespace video;
        set_mode(4);
        enable_bg(2);
    }
    {
        namespace mode = gba::video::mode4;
        mode::draw_horizontal_line(10, 20, 10, 0x1F);
    }
    return 0;
}
