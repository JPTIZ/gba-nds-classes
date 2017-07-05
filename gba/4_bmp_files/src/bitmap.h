#ifndef BMP2H_BITMAP_H
#define BMP2H_BITMAP_H

#include <string>
#include <vector>
#include <utility>

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

    auto stride() const {
      return 4 * ((bpp * width + 31)/32);
    }

    auto size() const {
      return width * height;
    }
} __attribute__((packed));

using Color = std::uint16_t;

struct Bitmap {
  BitmapFileHeader file_header;
  BitmapInfoHeader info_header;
  std::vector<std::uint8_t> data;
  std::vector<Color> palette;

  Bitmap(BitmapFileHeader file_header, BitmapInfoHeader info_header):
      file_header{std::move(file_header)},
      info_header{std::move(info_header)}
  {}

  auto width() const {
      return info_header.width;
  }

  auto height() const {
      return info_header.height;
  }
};

Bitmap make_palette(Bitmap, std::vector<Color>);
Bitmap load_bitmap(std::string filename);
void save_header(const Bitmap& bitmap, const std::string& filename);

}

#endif
