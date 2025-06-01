#include "./image-reader.cpp"
#include "./pixels.cpp"

int main() {
    Pix_map img = read_img("../assets/fighter-jet-160x90.jpg");

    for (size_t y = 0; y < img.size(); ++y) {
        for (size_t x = 0; x < img[y].size(); ++x) {
            Pixel(x, y, img[y][x]);
        }
    }

    Pixel::draw_pixels();

    return 0;
}