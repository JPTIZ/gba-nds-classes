# Class 1 - Exploring Mode 3

## Summary

1. Bitmapped Modes Overview
2. Performance Issues in Mode 3
3. VSync

## 1. Bitmapped Modes Overview

### Accessing memory addresses in C++

```C++
*(std::uint16_t*)0x4000000 = 0x403;
*(std::uint16_t*)0x6000000 = 0x1EF;
```

### How to fill screen

```C++
auto screen_width = 240;
auto screen_height = 160;
for (auto x = 0u; x < screen_width; ++x) {
  for (auto y = 0u; y < screen_height; ++y) {
    ((std::uint16_t*)0x6000000)[x + screen_width*y] = 0x1EF;
  }
}
```

## 2. Performance Issues in Mode 3

1. Filling the screen is expensive;
2. Drawing anything frequently on screen is expensive;
3. You can even see things drawing randomly;
4. Why does item 3 happens?

Answers:

1. Each pixel takes 4 cycles to be drawn by PPU, that means you have 240x160
pixels to be drawn by PPU times 4 cycles per pixel, which takes 153600 cycles to
fill screen with data already on VRAM. But you don't have just the visible
screen, but also 68 more pixels per scanline (a row of pixels) and 68 more
scanlines. That is, 308x228x4 = 280896 PPU cycles for filling screen.
So, we have:
  - 1232 cycles for drawing a single scanline;
  - 153.6K cycles for drawing visible screen (without 68 extra pixels/scanline);
  - 197.1K cycles for drawing visible screen (with 68 extra pixels/scanline);
  - 280.9K cycles for filling entire screen.
Each PPU cycle takes about 16.77us to be complete.
  but looping through screen and
 filling data

###

