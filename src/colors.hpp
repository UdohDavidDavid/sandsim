#ifndef COLOR_HPP
#define COLOR_HPP

#include "raylib.h"
#include <vector>
#include <random>

inline std::vector <Color> sand_colors = {
    {226, 209, 115, 255},
    {238, 221, 127, 255},
    {217, 200, 106, 255},
};

inline int pick_a_color(std::vector<Color> &color) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, color.size() - 1);
    return dist6(rng);
}

#endif