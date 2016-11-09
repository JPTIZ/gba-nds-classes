# Class 2 - Modes 4 and 5, and Palettes

## Summary

1. What is page-flipping
2. What's new about mode 5
3. What's new about mode 4

## 1. What is page-flipping

Page-flipping is a techique to prevent VRAM changes to overlap video drawing.

### How does page-flipping works?

Page-flipping works just as follows:

You have 2 pages (at least). These pages are nothing more than...a frame of
your screen. But, from those two, you show only one at a time. You use the
second one to be filled while the first (which should be already filled) is
shown. When the second one is ready, you shift to show it and start filling
the first one with the next frame of the game. This way you ensure that the
screen only shows frames that are already done, and does not show any "half-
filled and undone frame".

### Page-flipping is not Double-buffering!

Although both use two buffers, in page-flipping you just change the video
buffer pointer to one of the two pages - there's no copy! In double buffering,
you have two buffers, you write on the back (invisible) buffer and **copy** it
to the front (visible) buffer.

### How to use page-flipping in GBA

When you're on page-flippable modes, VRAM is divided in two sections (which are
the front and back buffers). So, lets say our screen is 100x50, 16bit bitmapped
data, and VRAM starts at 0x06000000. So, our page size will be 100x50x2 = 1000
bytes = 0x3E8 bytes, that means our first page starts at 0x06000000 and our
second page starts at 0x060003E8.

Then, when we're drawing to the first page, we can do:

```C++
reinterpret_cast<std::uint16_t*>(0x6000000)[x + 100*y] = color;
```

And for the second page:

```C++
reinterpret_cast<std::uint16_t*>(0x60003E8)[x + 100*y] = color;
```

Now, let's suppose we finished drawing a page and want to flip them (to show
our completed page and start drawing in the other). On control register, the
4th bit represents what page is being drawn (0 = page 0, 1 = page 1). Then we
need only to change it with a XOR (^):

```C++
gba::video::lcd_control() ^= gba::video::LCDControl::PAGE_BIT;
```

To make things simpler, we could have a variable `page` and a procedure
`flip_pages()` (or just `flip()`) that makes `vram_` point between the two
pages' initial address:

```C++
namespace gba {
namespace video {

std::uint16_t* page = 0x6000000;

void flip_pages() {
    lcd_control() ^= LCDControl::PAGE_BIT;
    auto current_page = lcd_control() & LCDControl::PAGE_BIT;
    page = reinterpret_cast<std::uint16_t*>(0x6000000 + 0x3E8 * current_page);
}

}
}
```

## 2. What's new about mode 5

1. Screen size is 160x128;
3. It has page-flipping;
4. At least we use 100% of VRAM;

## 3. What's new about mode 4

1. It's paletted (8bpp entries for 16bit colors);
2. Data must be read before writing (because VRAM/OAM/Palette bus is 16-bit);
3. Still page-flippable;
4. But, for OAM and Palette you won't bother (they store 16-bit stuff already);
5. We have 100% of VRAM use (40KB/page out of 80KB VRAM size)!

What's old? Still 240x160. Which is sorta better.

### How does palette works?

Palette works just as an array: Your bitmapped data has indexes to the palette,
while the palette has color values.


That is, if your palette is:

```
palette = [black, red, green, blue, white]
```

And your bitmapped data is:

```
0 0 1 1 1 1 0 0
0 1 0 0 0 0 1 0
1 0 3 0 0 3 0 1
1 0 0 0 0 0 0 1
1 0 1 0 0 1 0 1
1 0 0 1 1 0 0 1
0 1 0 0 0 0 1 0
0 0 1 1 1 1 0 0
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
