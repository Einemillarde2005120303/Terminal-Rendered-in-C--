#include <iostream>
#include <vector>
#include <tuple>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

typedef std::vector<std::vector<std::tuple<int, int, int>>> Pix_map;

Pix_map read_img(const std::string& path) {
    int width, height, channels;
    unsigned char* img = stbi_load(path.c_str(), &width, &height, &channels, 3);

    if (!img) {
        std::cerr << "Error: Failed to load image!" << std::endl;
        return {};
    }

    Pix_map pixels(height);
    for (int i = 0; i < height; ++i) {
        pixels[i].reserve(width);
        for (int j = 0; j < width; ++j) {
            int idx = (i * width + j) * 3;
            pixels[i].emplace_back(img[idx], img[idx + 1], img[idx + 2]);
        }
    }

    stbi_image_free(img);
    return pixels;
}
