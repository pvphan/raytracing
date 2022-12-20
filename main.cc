#include <iostream>

#include "color.h"
#include "vec3.h"


int main() {
    // Image
    const int imageWidth = 256;
    const int imageHeight = 256;

    // Render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
    for (int j = imageHeight-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            color pixelColor(
                    double(i) / (imageWidth-1),
                    double(j) / (imageHeight-1),
                    0.25
            );
            writeColor(std::cout, pixelColor);
        }
    }
    std::cerr << "\nDone.\n";
    return 0;
}
