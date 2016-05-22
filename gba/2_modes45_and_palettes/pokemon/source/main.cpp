#include <cstdint>
#include "gba.h"
#include "video_operations.h"

int main() {
    {
        using namespace gba::video;
        // Sets mode 3
        lcd_control() = 3;
        enable_bg(2);
    }
    gba::video::draw_rect(0, 30, 240, 100, gba::video::Color{5u, 5u, 10u});
    while (true) {};
    return 0;
}
