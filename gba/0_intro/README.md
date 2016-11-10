Intro-Class - Introduction to GBA Hardware
==========================================

Summary
-------

1. Old console history
2. Inside the GBA
3. Introduction to Video Memory
4. Emulating GBA + Dev Tools


1) Old consoles history
-----------------------

### Atari 2600

About:
 - Year: 1977
 - Processor: MOS Technology 6507
 - Bus: 8bit
 - Clock: 1.19MHz
 - RAM: 128B
 - ROM: 16KB
 - Resolution: 160x192 (NTSC), 160x228 (PAL)
 - Colors: 128
 - Sound: 2 channels (1 chip each)

Development Specifications:
 - Had for 2 player's sprites with Hardware Acceleration
 - Fully bitmapped
 - Maximum of 2 sprites on the same scanline

### NES

About:
 - Year: 1983
 - Processor: Custom MOS 6502
 - Bus: 8bit
 - CPU Clock: 1.79MHz (NTSC), 1.66MHz (PAL)
 - GPU Clock: 5.37MHz (NTSC), 5.33MHz (PAL)
 - RAM: 2KiB + Cartdridge expansion RAM
 - ROM: 48KB
 - Resolution: 256x240
 - Max sprites on screen: 64
 - Sound: see dev-specs

Development Specifications:
 - Palette: 56 colors
 - OAM: 256B
 - Colors on screen: 25 colors/scanline
   - BG
   - 4 sets of 3 colors for tiles
   - 4 colors per sprites
 - Sprite dimensions:
   - 16x16
   - 24x24
 - Sound: 5 channels
   - 2 square
   - 1 triangle
   - 1 white noise
   - 1 delta-pulse code modulation (DPCM) of 6 bits

### SNES

About:
 - Year: 1990
 - Processor: Nintendo's custom Ricoh 5A22
 - Bus: 16bit
 - CPU Clock: 1.79MHz, 2.68MHz or 3.58MHz
 - GPU Clock: Same as CPU
 - RAM: 128KB
 - VRAM: 64KB
 - Audio RAM: 64KB
 - Resolution: 256x224/512x448

Development Specifications:
 - Palette: 15 bits (32768 colors)
 - OAM: 544B
 - Sprite dimensions:
   - 8x8
   - 16x16
   - 32x32
   - 64x64
 - Colors per sprite: 16
 - Max sprites on screen: 128 (32/scanline)
 - Background Layers: 4
 - Sound: 8 channels, 32KHz 16-bit Stereo

### GameBoy

About:
 - Year: 1989
 - Processor: Custom Sharp LR35902
 - Bus: 8bit
 - CPU Clock: 4.19MHz
 - RAM: 8KB (can be expanded to 32KB)
 - ROM:
   - Internal: 256B
   - Cartdridges: 256K/512K/1M/2M/4M/8MB
 - VRAM: 8KB (internal)
 - Resolution: 160x144
 - Colors: 2 bits (4 "graytones")

Development Specifications:
 - OAM: 160B (4B/sprite)
 - Sprite dimensions:
   - 8x8
   - 8x16
 - Color per sprite: 16 colors
 - Max sprites on screen: 40
 - Sound: 2 wave pulse generators

### GameBoy Advance

About:
 - Year: 2001
 - Processor: ARM7-TDMI¹ with embedded memory
 - Bus: 16bit
 - Co-Processor: Z80 8bit 4/8MHz (for GB/GBC compatibility)
 - CPU Clock: 16.8MHz
 - GPU Clock: ~5.5MHz (59.73FPS)
 - RAM: 32KB (CPU)
 - VRAM: 92KB (internal)
 - DRAM: 256KB (external to CPU)
 - Resolution: 240x160 (3:2)

Development Specifications:
 - Palette: 15-bit X1B5G5R5
   - Character Mode: 512 colors
   - Bitmapped Mode: 32768 colors
 - OAM: 160B (4 bytes/sprite)
 - Sprite dimensions:
   - 8x8
   - 8x16
   - 16x8
   - 16x16
 - Colors: 1 palette for entire screen (256 colors)
 - Max sprites on screen: 256
 - Sound: Dual 8-bit DAC² for Stereo Sound (DirectSound)

     ¹: ARM + 16-bit Thumb + JTAG Debug + fast Multiplier + enhanced ICE
     ²: Digital-Analogic Converter


2) Inside the GBA
-----------------

### Hardware overview

Components that can be identified:
 - D-pad, A, B, L, R and Start/Select Buttons
 - Processor & Co-processor (side by side)
 - Audio Processor
 - U3 GBA Registers
 - Cartdridge:
   - ROM
   - SaveData

Each one has addresses related to an item about them.
Read-Only Addresses:
 - Buttons
 - Some internal registers (ex: scanline count register)
 - ROM (bup)

Write-Only Addresses:
 - Interrupts (!)
 - Some internal registers

(!): Altough Interrupts are read-only, you can perform `or` operations
     with them, but you MUST NOT! It can bring unwanted behaviours, since
     it'll wait for all interrupts setted to be thrown.

### Memory Addresses

Every memory address has its section specified by their first 2 hex characters:

    - 0x00XXXXXX: BIOS - System ROM
    - 0x02XXXXXX: WorkRAM On-board
    - 0x03XXXXXX: WorkRAM On-chip
    - 0x04XXXXXX: IO Registers
    - 0x05XXXXXX: BG/OBJ Palette RAM
    - 0x06XXXXXX: VRAM
    - 0x07XXXXXX: Object Attribute Memory (OAM)

    - 0x08XXXXXX and 0x09XXXXXX: GamePakROM/FlashROM (WS0)
    - 0x0AXXXXXX and 0x0BXXXXXX: GamePakROM/FlashROM (WS1)
    - 0x0CXXXXXX and 0x0DXXXXXX: GamePakROM/FlashROM (WS2)

    - 0x0EXXXXXX: GamePakSRAM

Memory addresses from 0x10000000 to 0xFFFFFFFF are unused.


3) Introduction to Video Memory
-------------------------------

### How does GBA Video work

GBA Video is managed by some registers, each one with bitmasked functions.

First there is the Display Control Register, which is mapped like:

```
wwwobbbbfohpcmmm
```

Where...

    www: enables window mode for objects, window layer 1 and window layer 0,
         respectively;
    o: enables object layer;
    bbbb: enables background layers 3, 2, 1 and 0, respectively;
    f: forces blank screen;
    o: object mapping mode (0 = 1D array, 1 = 2D array);
    h: enables OAM access when in HBlank;
    p: page selection (used for page-flipping);
    c: cgb(1) or gba(0) modes;
    mmm: enable mode 0bmmm (as an integer from 000b to 100b). 110b and 111b
         are invalid).

Display Control Register is located at address 0x04000000.

### Brief look to Mode 3

Mode 3 is composed by a matrix of 16-bit integers, each one representing a
xb5g5r5 color (bgr map), that is: 1 unused bit, 5 bits for blue, 5 bits for
green, 5 bits for red.

Each pixel can be accessed by the general formula:

`
vram[x + screen_width * y]
`

This happens because the screen is actually an array of pixels, not a matrix.

VRAM starts at address 0x06000000.

So, in C++, to change pixel (4, 2) to red, you can write:

```C++
reintrepret_cast<std::uint16_t*>(0x06000000)[4, 2] = 0x1F;
```

Since 1F = 31 = 0b0000000000011111.

### Some ARM7TDMI Assembly

#### MOV `destiny`, `origin`:
Moves origin data to destiny register. Origin may be either a register or a
constant.

Note that MOV instruction, in case of constants, stores a 8-bit constant +
4-bits for shifting. That exists to store bigger constants. For an example, if
you want to store 0b1000000000000000, which doesn't fit in an 8-bit constant,
you can store 0b10 and shift right it two times (the 4-bit for shifting is
always multiplied by two).

#### STRH `origin`, [`destiny`(, `offset`)]:
Stores the contents of a halfword size register `origin` into `destiny`. You
may sum it with a constant or the value of another register.

#### ADD `destiny`, `operand 1`, #`8bit constant`:
Performs the operation:
        <destiny> = <operand 1> + <constant>

#### (pseudo) LDR `destiny`, =#`32bit constant`:
Generates the best sequence of instructions to store the 32-bit constant into
destiny register.

Some examples:

```
mov r0, #0x400      ; stores 0x400 into register r0
add r0, r0, #3      ; adds 3 to r0 (to match 0x403)
mov r1, #0x4000000  ; stores address 0x4000000 to r1
strh r0, [r1]       ; stores #0x403 into memory address 0x4000000
```

The same could be rewritten into:

```
ldr r0, =#0x403     ; stores 0x403 into register r0
mov r1, #0x4000000  ; stores address 0x4000000 to r1
strh r0, [r1]       ; stores 0x403 into memory address 0x4000000
```

Now, to draw an orange pixel (0x1EF) into the top-left point on screen:

```
ldr r1, =#0x6000000 ; stores address 0x6000000 to r1
ldr r0, =#0x1EF     ; stores 0x1EF into r0
strh r0, [r1]       ; stores 0x1EF into memory address 0x6000000
```


### Compiling with DevKitPro

#### Compile C++ code

Not that much to add. Just compile as it was a common C++ code, but using
DevKitARM compiler instead of pure-G++.

```
arm-none-eabi-g++ -mthumb -mthumb-interwork -c file.cpp
```

Flags:
 - `-mthumb` enables 16-bit Thumb instructions mode.
 - `-mthumb-interwork` enables change between 16-bit Thumb and 32-bit ARM
          instructions in runtime.
 - `-c <file>` tells compiler to not generate an executable file, just an
          object file.
 - [extra]
   - `-O2` tells compiler to perform level-2 optimizations.
   - `-O3` tells compiler to perform level-3 (maximum) optimizations.
   - `-Os` tells compiler to perform optimize binary output size.

#### Linking to an ELF (Executable and Linkable File)

```
arm-none-eabi-g++ -specs=gba.specs -mthumb -mthumb-interwork file.o -o file.elf
```

Linking is the process in which libraries (.a) and object (.o) files are mixed
together into only one .elf file.

And ELF file is a common stardard file format for executables, object code,
shared libraries and core dumps. A .bin file is also an ELF file.

#### Removing debug symbols from ELF file

```
arm-none-eabi-objcopy -O binary file.elf file.gba
```

The above operation strips the ELF removing debug symbols such as breakpoint
instructions.

#### Fixing header

Each GBA game has a checksum to make sure it is a valid GBA binary. It doesn't
have a default tool for making this operation, so it shall be used a third-
party tool such as `gbafix` by DarkFader.

```
gbafix file.gba
```


4) Emulating GBA + Dev Tools
----------------------------

Welp, this is for VBA stuff. It has...

 - Disassemble;
 - Memory View;
 - Map Viewer;
 - Tile Viewer;
 - OAM Viewer;
 - Enable/Disable layers (runtime).

The End. Let's move on to the next class =)
