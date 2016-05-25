# Class 2 - Modes 4 and 5, and Palettes

## Summary

1. What is page-flipping
2. What's new about mode 5
3. What's new about mode 4

## 1. What's new about mode 5

1. Screen size is 160x128;
3. It has page-flipping;
4. At least we use 100% of VRAM;

## 2. What's new about mode 4

1. It's paletted (8bpp entries for 16bit colors);
2. Data must be read before writing (because VRAM/OAM/Palette bus is 16-bit);
3. Still page-flippable;
4. But, for OAM and Palette you won't bother (they store 16-bit stuff already);
5. We have 100% of VRAM use (40KB/page out of 80KB VRAM size)!

What's old? Still 240x160.

### How does palette works?

Palette works just as an array: Your bitmapped data has indexes to the palette,
while the palette has color values.


That is, if your palette is:

```
palette = [black, red, green, blue, white]
```

And your bitmapped data is:

```
0 0 1 1 1 0 0
0 1 0 0 0 1 0
1 0 3 0 3 0 1
1 0 0 0 0 0 1
1 0 1 0 1 0 1
0 1 0 1 0 1 0
0 0 1 1 1 0 0
```

You basically will have (what was to be) a happy red smily face with blue eyes,
as it would be:

```
black black  red   red   red  black black
black  red  black black black  red  black
 red  black blue  black blue  black  red
 red  black black black black black  red
 red  black  red  black  red  black  red
black  red  black  red  black  red  black
black black  red   red   red  black black
```

Because 0 (the first index of the palette) is black, index 1 is red, and index
3 is blue.

### How does page-flipping works?

Page-flipping works just as follows:

You have 2 pages (at least). These pages are nothing more than...a frame of
your screen. But, from those two, you show only one at a time. You use the
second one to be filled while the first (which should be already filled) is
shown. When the second one is ready, you shift to show it and start filling
the first one with the next frame of the game. This way you ensure that the
screen only shows frames that are already done, and does not show any "half-
filled and undone frame".



