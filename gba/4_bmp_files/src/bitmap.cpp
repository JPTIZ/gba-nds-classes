#include "bitmap.h"

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <experimental/filesystem>

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

    file.seekg(file_header.data_begin, std::ios::beg);

    auto data_size = bmp_header.height * bmp_header.width;
    Color<16> data[data_size];
    for (auto i = 0u; i < data_size; ++i) {
        file.read(reinterpret_cast<char*>(data + i), sizeof(data[0]));
    }

    std::vector<Color<16>> data_v(data, data + data_size);
    return Bitmap{file_header, bmp_header, data_v};
}

void converter::save_header(const Bitmap& bitmap, const std::string& filename_) {
    using namespace std::experimental::filesystem;

    auto filename = path{filename_}.replace_extension("h");
    std::cout << "saving " << filename << '\n';

    std::stringstream contents;

    {
        auto guard = std::string{path{filename}.filename().replace_extension("")};
        for (auto& c: guard) {
            c = std::toupper(c);
        }

        std::replace(std::begin(guard), std::end(guard), '/', '_');
        guard += "_H";

        contents << "#ifndef MYGAME_RESOURCES_" << guard << '\n'
                 << "#define MYGAME_RESOURCES_" << guard << '\n';
    }

    {
        auto filename = filename_;
        for (auto& c: filename) {
            c = std::tolower(c);
        }

        auto name = std::string{path{filename_}.stem()};

        auto palette_size = 16;
        contents << "\n#include <cstdint>\n"
                 "\nnamespace mygame::resources {\n\n"
                 "auto " << name << "_width = "
                 << bitmap.info_header.width << ";\n"
                 "auto " << name << "_height = "
                 << bitmap.info_header.height << ";\n\n"
                 "std::uint16_t " << name << "_palette["
                 << palette_size << "] = {\n"
                 "};\n"
                 "\nstd::uint16_t " << name << "_data["
                 << (bitmap.info_header.size() / 2) << "] = {\n"
                 "};\n";
    }


    contents << "\n}\n"
        "\n#endif\n";

    std::ofstream file(filename);
    file << contents.str();
}
