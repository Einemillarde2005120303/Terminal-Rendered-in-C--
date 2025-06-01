#include "./image-reader.cpp"
#include "./pixels.cpp"
#include <chrono>

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    Pix_map img = read_img("../assets/fighter-jet-160x90.jpg");
    Pixel::delete_pixels();
    for (size_t y = 0; y < img.size(); ++y) {
        for (size_t x = 0; x < img[y].size(); ++x) {
            Pixel(x, y, img[y][x]);
        }
    }
    Pixel::draw_pixels();

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    double fps = 1 / duration.count();

    std::cout << "\nFPS: " << fps;

    return 0;
}