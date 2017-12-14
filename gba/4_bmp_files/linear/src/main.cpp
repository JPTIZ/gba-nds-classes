#include <iostream>

#include "bitmap.h"

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "usage: bmp2h filename\n";
        return 0;
    }

    try {
        auto bitmap = converter::load_bitmap(argv[1]);
        converter::save_header(bitmap, std::string(argv[1]));
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
    }
}
