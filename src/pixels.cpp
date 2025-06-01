#include <sstream>
#include <iostream>
#include <unordered_map>
#include <tuple>
#include <windows.h>

const std::string block = "\u2580";
const std::string reset = "\x1b[0m";

std::string fg(int r, int g, int b) {
    return "\x1b[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

std::string bg(int r, int g, int b) {
    return "\x1b[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

std::string pos(int x, int y) {
    return "\x1b[" + std::to_string(y) + ";" + std::to_string(x) + "H";
}

struct pair_hash {
    size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

class Pixel {
    private:
        inline static std::unordered_map<std::pair<int, int>, std::tuple<int, int, int>, pair_hash> pixel_map;

    public:
        Pixel(int x, int y, std::tuple<int, int, int> color) {
            pixel_map[{x, y}] = color;
        }

        static void draw_pixels() {
            SetConsoleOutputCP(CP_UTF8);
            std::ostringstream oss;
            oss << "\x1b[2J\x1b[H";

            for (const auto& [coord, color] : pixel_map) {
                int x = coord.first;
                int y = coord.second;

                int fg_[3] = {0, 0, 0};
                int bg_[3] = {0, 0, 0};

                if (y % 2 == 0) {
                    fg_[0] = std::get<0>(color);
                    fg_[1] = std::get<1>(color);
                    fg_[2] = std::get<2>(color);

                    auto it = pixel_map.find({x, y + 1});
                    if (it != pixel_map.end()) {
                        auto c = it->second;
                        bg_[0] = std::get<0>(c);
                        bg_[1] = std::get<1>(c);
                        bg_[2] = std::get<2>(c);
                    }
                } else continue;

                oss << pos(x + 1, (y / 2) + 1)
                    << fg(fg_[0], fg_[1], fg_[2])
                    << bg(bg_[0], bg_[1], bg_[2])
                    << block << reset;
            }

            std::cout << oss.str() << "\x1b[2J\x1b[H" << std::flush;
        }

        static void delete_pixels() {
            pixel_map.clear();
        }
};
