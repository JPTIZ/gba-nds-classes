#ifndef BMP2H_BITMAP_H
#define BMP2H_BITMAP_H

#include <string>

namespace converter {

struct BitmapFileHeader {
    std::uint16_t file_type;
    std::uint32_t file_size;
    std::uint16_t reserved_06;
    std::uint16_t reserved_08;
    std::uint32_t data_begin;

} __attribute__((packed));

enum class CompressionMethod: std::uint32_t {
    RGB = 0,
    RLE8,
    RLE4,
    BITFIELDS,
    JPEG,
    PNG,
    ALPHABITFIELDS,
    CMYK = 11,
    CMYKRLE8,
    CMYKRLE4,
};

struct BitmapInfoHeader {
    std::uint32_t header_size;
    std::int32_t width;
    std::int32_t height;
    std::uint16_t color_planes{1};
    std::uint16_t bpp{1};
    CompressionMethod compression_method;
    std::uint32_t raw_size{0};
    std::int32_t horizontal_ppm;
    std::int32_t vertical_ppm;
    std::uint32_t palette_size{0};
    std::uint32_t important_colors{0};
} __attribute__((packed));

template <std::size_t BPP>
struct Color {
    char value[BPP / 8];
};

struct Bitmap {

};

Bitmap load_bitmap(std::string filename);

}

#endif
