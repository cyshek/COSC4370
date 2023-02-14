#include <iostream>
#include "BMP.h"
#include <cmath>

using namespace std;

void fill_pixel(BMP &bmp, int32_t x, int32_t y, uint8_t red, uint8_t green, uint8_t blue) {
    // Calculate the index of the pixel to be filled
    int32_t index = (y * bmp.bmp_info_header.width + x) * bmp.bmp_info_header.bit_count / 8;

    // Fill the pixel with the given RGB values
    bmp.data[index + 0] = red;
    bmp.data[index + 1] = green;
    bmp.data[index + 2] = blue;

    // If the image has 4 channels (RGBA), fill the alpha channel with 255 (fully opaque)
    if (bmp.bmp_info_header.bit_count == 32) {
        bmp.data[index + 3] = 255;
    }
}

void fill_ellipse_pixel(BMP &bmp, int32_t x, int32_t y) {
    // Calculate the adjusted x and y values
    int32_t half_width = bmp.bmp_info_header.width / 2;
    int32_t adjusted_x = x - half_width;
    int32_t half_height = bmp.bmp_info_header.height / 2;
    int32_t adjusted_y = half_height - y;

    // Check if the point (x, y) lies inside the ellipse
    if (pow(adjusted_x / 6.0, 2) + pow(adjusted_y / 12.0, 2) <= pow(64, 2)) {
        // Fill the pixel with the appropriate color based on its x coordinate
        if (x < (bmp.bmp_info_header.width / 3)) {
            fill_pixel(bmp, x, y, 255, 0, 0);
        } else if (x >= (bmp.bmp_info_header.width / 3) && x < (2 * bmp.bmp_info_header.width / 3)) {
            fill_pixel(bmp, x, y, 255, 165, 0);
        } else {
            fill_pixel(bmp, x, y, 255, 255, 0);
        }
    }
}

void rasterize_ellipse (BMP &bmp) {
    // Iterate over each row of the image
    for (int32_t y = bmp.bmp_info_header.height / 2; y < bmp.bmp_info_header.height; ++y) {
        // Iterate over each column of the image
        for (int32_t x = 0; x < bmp.bmp_info_header.width; ++x) {
            fill_ellipse_pixel(bmp, x, y);
        }
    }
}

int main() {
    // create a new instance of the BMP class with width of 1600 and height of 2000
    BMP newObj(1600, 2000, false);

    // call the rasterize_ellipse function on the new instance of the BMP class
    rasterize_ellipse(newObj);

    // write the image data to the file "output.bmp"
    newObj.write("output.bmp");

    return 0;
}












