#include "bitmap.h"

#include <string>
#include <fstream>
#include <iostream>

using converter::Bitmap;

Bitmap converter::load_bitmap(std::string filename) {
    std::cout << "loading " << filename << '\n';

    std::ifstream file(filename, std::ios::binary);
    return Bitmap{};
}
