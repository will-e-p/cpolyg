#pragma once

#include <array>

// Provide quadrature points and weights for various degree polynomials
// For integrals over lines and triangles
struct Quadratures
{
    static std::array<std::array<double, 2>, 2> lin2;
    static std::array<std::array<double, 2>, 4> lin4;
    static std::array<std::array<double, 2>, 6> lin6;
    static std::array<std::array<double, 2>, 10> lin10;
    
    static std::array<std::array<double, 3>, 3> tri2;
    static std::array<std::array<double, 3>, 6> tri4;
    static std::array<std::array<double, 3>, 12> tri6;
    static std::array<std::array<double, 3>, 25> tri10;
};
