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

```
auto screen_width = 240;
auto screen_height = 160;
for (auto x = 0u; x < screen_width; ++x) {
  for (auto y = 0u; y < screen_height; ++y) {
    ((std::uint16_t*)0x6000000)[x + screen_width*y] = 0x1EF;
  }
}
```

### How to draw a rectangle on screen

```C++
auto rect_width = 32u;
auto rect_height = 32u;
auto rect_x = 16u;
auto rect_y = 120u;

for (auto x = rect_x; x < rect_x + rect_width; ++x) {
  for (auto y = rect_y; y < rect_y + rect_height; ++y) {
    ((std::uint16_t*)0x6000000)[x + screen_width*y] = 0x1EF;
  }
}

```

### How to draw a Line

Lazy way:

```C++
auto x0 = 32u;
auto x1 = 64u;
auto y0 = 32u;
auto y1 = 96u;

auto dx = x1 - x0;
auto dy = y1 - y0;

if (dx > dy) {
    for (auto y = y0; y < y1; ++y) {
        auto x = x0 + dx * (y - y0) / dy;
        auto next_x = x0 + dx * (y + 1 - y0) / dy;
        for (auto x_ = x; x_ < next_x; ++x_) {
            gba::video::vram(x_, y, color);
        }
    }
} else {
    for (auto x = x0; x < x1; ++x) {
        auto y = y0 + dy * (x - x0) / dx;
        auto next_y = y0 + dy * (x + 1 - x0) / dx;
        for (auto y_ = y; y_ < next_y; ++y_) {
            gba::video::vram(x, y_, color);
        }
    }
}
```

### How to draw a circle

```C++
auto x = 0u;
auto y = radius;
auto 
```


