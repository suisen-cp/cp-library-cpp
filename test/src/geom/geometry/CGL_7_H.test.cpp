#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H"
#define ERROR 0.00001

#include <cassert>
#include <iostream>
#include <iomanip>

#include "library/geom/geometry.hpp"

using namespace suisen::geometry;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(20);

    int n;
    coordinate_t r;
    std::cin >> n >> r;
    Polygon poly(n);
    for (auto &p : poly) std::cin >> p;
    std::cout << intersection_area(poly, Circle(ZERO, r)) << '\n';
    return 0;
}