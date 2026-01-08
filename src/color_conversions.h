#pragma once

#include <array>

std::array<double, 3>
rgb_to_hsl(double r, double g, double b);

std::array<double, 3>
hsl_to_rgb(double h, double s, double l);

std::array<double, 3>
rgb_to_xyz(double r, double g, double b);

std::array<double, 3>
rgb_to_lab(double r, double g, double b);

std::array<double, 3>
rgb_to_lch(double r, double g, double b);
