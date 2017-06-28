#include "bitmap.h"

#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>

using converter::Bitmap;
using converter::BitmapFileHeader;
using converter::BitmapInfoHeader;


namespace {
    auto load_header(std::ifstream& file) {
        BitmapFileHeader header;
        std::cout << "sizeof(header): " << sizeof(header) << '\n';
        file.read(reinterpret_cast<char*>(&header), sizeof(header));
        return std::move(header);
    }

    auto load_bmp_header(std::ifstream& file) {
        BitmapInfoHeader header;
        std::cout << "sizeof(header): " << sizeof(header) << '\n';
        file.read(reinterpret_cast<char*>(&header), sizeof(header));
        return std::move(header);
    }

    void show_data(const BitmapFileHeader& header) {
        using std::setw;
        std::cout <<
            "|----------------------|\n"
            "|  Bitmap File Header  |\n"
            "|----------------------|\n"
            "| File Type | " << setw(8) << header.file_type << " |\n"
            "| File Size | " << setw(8) << header.file_size << " |\n"
            "| DataBegin | " << setw(8) << header.data_begin << " |\n"
            "|----------------------|\n";
    }

    auto method_name(converter::CompressionMethod method) {
        using converter::CompressionMethod;
        switch (method) {
            case CompressionMethod::RGB:
                return "RGB";
            case CompressionMethod::RLE8:
                return "RLE8";
            case CompressionMethod::RLE4:
                return "RLE4";
            case CompressionMethod::BITFIELDS:
                return "BITFIELDS";
            case CompressionMethod::JPEG:
                return "JPEG";
            case CompressionMethod::PNG:
                return "PNG";
            case CompressionMethod::ALPHABITFIELDS:
                return "ALPHABITFIELDS";
            case CompressionMethod::CMYK:
                return "CMYK";
            case CompressionMethod::CMYKRLE8:
                return "CMYKRLE8";
            case CompressionMethod::CMYKRLE4:
                return "CMYKRLE4";
            default:
                return "dunno";
        }
    }

    void show_data(const BitmapInfoHeader& header) {
        using std::setw;
        std::cout <<
            "|-------------------------------|\n"
            "|       Bitmap Info Header      |\n"
            "|-------------------------------|\n"
            "| Header Size  | " << setw(14) << header.header_size << " |\n"
            "| Width        | " << setw(14) << header.width << " |\n"
            "| Height       | " << setw(14) << header.height << " |\n"
            "| Color Planes | " << setw(14) << header.color_planes << " |\n"
            "| BPP          | " << setw(14) << header.bpp << " |\n"
            "| CompressMeth | " << setw(14) << method_name(header.compression_method) << " |\n"
            "| Raw BMP Size | " << setw(14) << header.raw_size << " |\n"
            "| Horizont.PPM | " << setw(14) << header.horizontal_ppm << " |\n"
            "| Vertical PPM | " << setw(14) << header.vertical_ppm << " |\n"
            "| Palette Size | " << setw(14) << header.palette_size << " |\n"
            "| ImportantClr | " << setw(14) << header.important_colors << " |\n"
            "|-------------------------------|\n";
    }
}


Bitmap converter::load_bitmap(std::string filename) {
    std::ifstream file(filename, std::ios::binary);
    if (not file.is_open()) {
        throw std::invalid_argument{"file \"" + filename + "\" not found."};
    }

    auto file_header = load_header(file);
    if (file_header.file_type != 0x4D42) {
        throw std::invalid_argument{"file is not a valid bitmap."};
    }

    auto bmp_header = load_bmp_header(file);

    show_data(file_header);
    show_data(bmp_header);

    for (auto i = 0u; i < bmp_header.width; ++i) {
        converter::Color<16> pixel;
        file.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));
        std::cout << *reinterpret_cast<std::uint16_t*>(&pixel.value) << '\n';
    }

    return Bitmap{};
}
