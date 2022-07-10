#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A"

#include <cassert>
#include <iostream>
#include <iomanip>

#include "library/integral_geom/geometry.hpp"

using namespace suisen::integral_geometry;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(20);

    Point c1, c2;
    coordinate_t r1, r2;
    std::cin >> c1 >> r1 >> c2 >> r2;
    std::cout << tangent_num(Circle(c1, r1), Circle(c2, r2)) << '\n';
    return 0;
}