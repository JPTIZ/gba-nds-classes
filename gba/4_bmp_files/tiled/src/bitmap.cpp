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
                    "std::uint16_t " << name << "_palette["
                 << bitmap.palette.size() << "] = {\n    ";

        contents << std::showbase << std::internal << std::setfill('0');

        for (auto i = 0u; i < bitmap.palette.size(); ++i) {
            auto color = bitmap.palette[i];
            color = (((color >> 10) & 0x1f) << 0) |
                    (((color >> 5) & 0x1f) << 5) |
                    (((color >> 0) & 0x1f) << 10);
            print_color(color);
            contents << std::setw(6) << std::hex << (short)color << ",\n    ";
        }

        const auto& data = bitmap.data;
        std::cout << "data.size(): " << data.size() << '\n';

        contents << "};\n"
                    "\nstd::uint16_t " << name << "_data["
                 << std::dec << (data.size() / 2) << "] = {\n";

        std::cout << "};\n"
                    "\nstd::uint16_t " << name << "_data["
                 << (data.size() / 2) << "] = {\n";

        for (auto i = 0u; i < bitmap.data.size() / 2; ++i) {
            if (i % 4 == 0) {
                contents << "\n    ";
            }
            if (i % 32 == 0) {
                contents << "\n    ";
            }
            auto index = (data[2 * i + 1] << 8) | (data[2 * i]);
            contents << std::setw(6) << std::hex << index << ", ";
        }

        contents << "};\n\n}\n"
                    "\n#endif\n";
    }
}


Bitmap converter::make_palette(Bitmap bitmap, std::vector<Color> data) {
    std::vector<Color> palette;
    std::vector<std::uint8_t> indices(data.size());

    auto bs = 8;
    auto w = bitmap.width();
    auto h = bitmap.height();
    std::cout << "height: " << h << "\n";
    auto x = 0;
    auto y = 0;
    for (auto i = 0u; i < data.size(); ++i) {
        auto index = std::find(palette.begin(), palette.end(), data[i]) - palette.begin();
        if (index == palette.size()) {
            palette.push_back(data[i]);
        }
        /*
            def foo(i, bs, w):
            ...   return (((i % bs) + bs*(i // (bs*bs)) % w), ((i % (bs*bs)) // bs) + bs * (i // (2*bs*bs)))
        */
        auto x = ((i % bs) + bs*(i / (bs*bs)) % w);
        auto y = ((i % (bs*bs)) / bs) + bs * (i / (2*bs*bs));
        if (i % w == 0) {
            std::cout << "\n";
        }
        std::cout << "[" << std::setw(3) << i << ":" << std::setw(2) << x << ", " << std::setw(2) << y << "], ";
        std::cout << "h - y: " << (h-y-1) << "\n";
        indices[x + w * (h-y-1)] = index;
    }
    std::cout << "\n";

    bitmap.palette = palette;
    bitmap.data = indices;
    return bitmap;
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
        std::cout << pixel << '\n';
    }

    // Loads color data
    file.seekg(file_header.data_begin, std::ios::beg);

    auto data_size = bmp_header.height * bmp_header.width;
    Color data[data_size];
    for (auto i = 0u; i < data_size; ++i) {
        file.read(reinterpret_cast<char*>(data + i), sizeof(Color));
    }

    std::vector<Color> data_v(data, data + data_size);
    return make_palette(std::move(Bitmap{file_header, bmp_header}), data_v);
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

        add_contents(contents, bitmap, std::string{path{class_name}.stem()});
    }

    std::ofstream file(filename);
    file << contents.str();
}
