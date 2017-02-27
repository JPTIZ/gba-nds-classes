#include "mode4.h"
#include "resources/zelda.h"

int main() {
    using namespace gba::resources;
    using namespace gba::video;
    using namespace gba::video::mode4;
    lcd_control() = gba::video::LCDControl::BG2 + 4;

    for (auto i = 1; i < 14; ++i) {
        palette_ram()[i] = zelda_palette[i];
    }
    while (true) {
        for (auto y = (short)0; y < 24; ++y) {
            for (auto x = (short)0; x < 12; ++x) {
                vram({x, y}) = zelda_data[x + 12 * y];
            }
        }
    }
}
