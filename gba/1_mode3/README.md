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
  - Each PPU cycle takes about 16.77us to be complete.

GBA's CPU frequency is 16.8MHz. That is, it can update VRAM much faster than
the PPU can draw it. So you basically can see screen being filled (actually
it happens really really fast, so you just try to see a very glitchy screen).

2. Screen size is 240x160. So to fill screen you have to perform _at least_
38400 iterations. That is...LOTS of iterations for every screen update. And
it isn't even considering drawing graphics such as sprites, HUDs...

3. Answered above (2).

4. Answered abote (1 and 2).

Every performance issue will be resolved as we proceed on this course, with new
techniques, exploring more and more our so limited (but powerful, somewhat)
hardware.

## 3. VSync

So, we must separate when do PPU draws stuff and when we setup the VRAM. You'll
find eventually that we also need to have a constant screen refreshing rate.
That is, in your game, it'll be essential to know how many frames have passed
since an event (that can even be the start of the game), and that must be
ensured to be at the same frequency every second. These things can be guaranteed
with something called Vertical Sync.

You don't want to draw when your screen's drawing, right? So you need to know
what is your PPU doing at an exactly moment. You can do that by just getting
wich line is PPU drawing right now, that is: an scanline counter.

Our PPU's scanline counter's value is stored at address 0x04000006. So when we
want to send things to VRAM, we can just while our scanline counter is less
than 160, and then we're ready to draw, since we have more 68 scanlines being
"drawn" on a "void of the screen" (not talking about `void` type here!).

So, we must just create our first "v_sync()" method:

```C++
void v_sync() {
  while (*reinterpret_cast<std::uint16_t*>(0x4000006)) {
    // Do nothing, just wait =)
  }
}
```

Now we're suposelly synching our screen with 60Hz (59.73 actually) refreshing
rate.

Yet, this is not a very good solution, for these reasons:

- We are throwing LOTS of CPU cycles away, that is waste of energy (take your
conclusions).
- Actually, our compiler will remove that while because it will think that it
does nothing and shoudn't be there;
- Actually[2], that does not synch exactly with 60Hz, to do that we should add a
few more code:

```C++
void v_sync() {
  volatile auto scanline_count = reinterpret_cast<std::uint16_t*>(0x4000006);
  while (*scanline_count >= 160) {}
  while (*scanline_count < 160) {}
}
