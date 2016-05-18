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


