#define cimg_use_png
#define cimg_use_jpeg
#include "CImg.h"
#include <cstdint>
#include <iostream>

using namespace cimg_library;

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cout << "Usage: resize <file-name>\n";
        return 0;
    }

    CImg<uint8_t> image(argv[1]);
    CImg<uint8_t> resized = image.get_resize(224, 180);

    CImgDisplay o(image, "original"), r(resized, "resized");

    while(!o.is_closed() && !r.is_closed()) {
        o.wait();
    }
    return 0;
}