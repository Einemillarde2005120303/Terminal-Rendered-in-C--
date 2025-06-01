#include <sstream>
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
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

class Pixel {
    private:
        inline static std::vector<std::pair<int, int>> coords = {};
        inline static std::vector<std::tuple<int, int, int>> colors = {};

    public:
        Pixel(int x, int y, std::tuple<int, int, int> color) {
            auto it = std::find(coords.begin(), coords.end(), std::make_pair(x, y));
            if (it != coords.end()) {
                size_t n = std::distance(coords.begin(), it);
                coords.erase(coords.begin() + n);
                colors.erase(colors.begin() + n);
            }
            coords.push_back({x, y});
            colors.push_back(color);
        }

        static void draw_pixels() {
            SetConsoleOutputCP(CP_UTF8);
            std::ostringstream oss;
            oss << "\x1b[2J\x1b[H";

            for (size_t n = 0; n < coords.size(); ++n) {
                int x = coords[n].first;
                int y = coords[n].second;
                auto color = colors[n];

                int fg_[3] = {0, 0, 0};
                int bg_[3] = {0, 0, 0};

                if (y % 2 == 0) {
                    fg_[0] = std::get<0>(color);
                    fg_[1] = std::get<1>(color);
                    fg_[2] = std::get<2>(color);

                    auto it = std::find(coords.begin(), coords.end(), std::make_pair(x, y + 1));
                    if (it != coords.end()) {
                        size_t idx = std::distance(coords.begin(), it);
                        auto c = colors[idx];
                        bg_[0] = std::get<0>(c);
                        bg_[1] = std::get<1>(c);
                        bg_[2] = std::get<2>(c);
                    }
                } else {
                    bg_[0] = std::get<0>(color);
                    bg_[1] = std::get<1>(color);
                    bg_[2] = std::get<2>(color);

                    auto it = std::find(coords.begin(), coords.end(), std::make_pair(x, y - 1));
                    if (it != coords.end()) {
                        size_t idx = std::distance(coords.begin(), it);
                        auto c = colors[idx];
                        fg_[0] = std::get<0>(c);
                        fg_[1] = std::get<1>(c);
                        fg_[2] = std::get<2>(c);
                    }
                }

                std::string p1 = pos(x + 1, (y / 2) + 1);
                std::string p2 = fg(fg_[0], fg_[1], fg_[2]);
                std::string p3 = bg(bg_[0], bg_[1], bg_[2]);

                oss << p1 << p2 << p3 << block << reset;
            }
            std::cout << oss.str() << std::flush;
        }

        static void delete_pixels() {
            coords.clear();
            colors.clear();
        }
};