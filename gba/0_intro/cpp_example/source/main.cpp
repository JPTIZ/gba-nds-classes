int main() {
    const auto dark_red = (unsigned short)0b10000;
    const auto red = (unsigned short)0b11111;
    const auto dark_blue = (unsigned short)0b10000 << 10;

    auto& display_control = *(unsigned short*)0x4000000;
    display_control = 0x403; // BG2 and Mode 3 enabled

    auto vram = (unsigned short*)0x6000000;

    // fills screen with dark-red and red lines
    for (auto y = 0u; y < 160u; ++y) {
        for (auto x = 0u; x < 240u; ++x) {
            if (y % 2 == 0) {
                vram[x + y*240] = dark_red;
            } else {
                vram[x + y*240] = red;
            }
        }
    }

    // draws a 64x48 rect on screen
    for (auto y = 48u; y < 96u; ++y) {
        for (auto x = 48u; x < 102u; ++x) {
            vram[x + y*240] = dark_blue;
        }
    }

    // main game loop
    while (true) {
    }
}
