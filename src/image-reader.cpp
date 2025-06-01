#include <iostream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

typedef std::vector<std::vector<std::tuple<int, int, int>>> Pix_map;

Pix_map read_img(std::string path) {
    int width, height, channels;
    unsigned char* img = stbi_load(path.c_str(), &width, &height, &channels, 3);

    if (!img) {
        std::cerr << "Error: Failed to load image!" << std::endl;
        return {};
    }


    std::vector<std::vector<std::tuple<int, int, int>>> pixels(height, std::vector<std::tuple<int, int, int>>(width, std::make_tuple(0, 0, 0)));

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            int idx = (i * width + j) * channels;
            pixels[i][j] = {img[idx], img[idx + 1], img[idx + 2]};
        }
    }

    stbi_image_free(img);

    return pixels;
}
