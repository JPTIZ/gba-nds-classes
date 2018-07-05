#include "bitmap.h"

#include <algorithm>
#include <experimental/filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

using converter::Bitmap;
using converter::BitmapFileHeader;
using converter::BitmapInfoHeader;

using namespace std::experimental::filesystem;

namespace {
    void print_color(converter::Color color) {
        std::cout << "(" << ((color >> 0) & 0x1f)
                  << ", " << ((color >> 5) & 0x1f)
                  << ", " << ((color >> 10) & 0x1f)
                  << ")," << std::endl;
    }


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


    auto basename(const std::string& filename) {
        return std::string{path{filename}.filename().replace_extension("")};
    }


    void add_include_guards(std::stringstream& contents, std::string guard) {
        for (auto& c: guard) {
            c = std::toupper(c);
        }

        std::replace(std::begin(guard), std::end(guard), '/', '_');
        std::replace(std::begin(guard), std::end(guard), '-', '_');
        guard += "_H";

        contents << "#ifndef MYGAME_RESOURCES_" << guard << '\n'
                 << "#define MYGAME_RESOURCES_" << guard << '\n';
    }


    void add_contents(std::stringstream& contents,
                      const Bitmap& bitmap,
                      const std::string& name) {
        contents << "\n#include <cstdint>\n"
                    "\nnamespace mygame::resources {\n\n"
                    "auto " << name << "_width = "
                 << bitmap.info_header.width << ";\n"
                    "auto " << name << "_height = "
                 << bitmap.info_header.height << ";\n\n"
                    "std::uint16_t __attribute__((section(\".ewram\"))) "
                 << name << "_data[] = {\n    ";

        contents << std::showbase << std::internal << std::setfill('0');

        auto w = bitmap.info_header.width;
        auto y = bitmap.info_header.height;
        for (auto i = 0u; i < bitmap.data.size(); ++i) {
            if (i % w == 0) {
                --y;
            }
            auto color = bitmap.data[i % w + y * w];
            color = (((color >> 10) & 0x1f) << 0) |
                    (((color >> 5) & 0x1f) << 5) |
                    (((color >> 0) & 0x1f) << 10);
            contents << std::setw(6) << std::hex << (short)color;
            if (i == bitmap.data.size() - 1) {
                contents << ",\n";
            } else if (i % 8 != 7) {
                contents << ",  ";
            } else {
                contents << ",\n    ";
            }
        }

        contents << "};\n"
                    "constexpr auto " << name << "_size ="
                    " sizeof(" << name << "_data) / sizeof(uint16_t);"
                    "\n\n}\n"
                    "\n#endif\n";
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
        converter::Color pixel;
        file.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));
    }

    // Loads color data
    file.seekg(file_header.data_begin, std::ios::beg);

    auto data_size = bmp_header.height * bmp_header.width;
    Color data[data_size];
    for (auto i = 0u; i < data_size; ++i) {
        file.read(reinterpret_cast<char*>(data + i), sizeof(Color));
    }

    auto bitmap = Bitmap{file_header, bmp_header};
    bitmap.data = std::vector<Color>(data, data + data_size);
    return bitmap;
}


void converter::save_header(const Bitmap& bitmap, const std::string& filename_) {
    auto filename = path{filename_}.replace_extension("h");
    std::cout << "saving " << filename << '\n';

    std::stringstream contents;
    add_include_guards(contents, basename(filename));
    {
        auto class_name = filename_;
        for (auto& c: class_name) {
            c = std::tolower(c);
        }
        std::replace(std::begin(class_name), std::end(class_name), '-', '_');

        add_contents(contents, bitmap, std::string{path{class_name}.stem()});
    }

    std::ofstream file(filename);
    file << contents.str();
}
