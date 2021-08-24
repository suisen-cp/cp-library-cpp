#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_I"
#define ERROR 0.000001

#include <cassert>
#include <iostream>
#include <iomanip>

#include "library/geom/geometry.hpp"

using namespace suisen::geometry;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(20);

    Point p1, p2;
    coordinate_t r1, r2;
    std::cin >> p1 >> r1 >> p2 >> r2;
    Circle c1(p1, r1), c2(p2, r2);
    std::cout << intersection_area(c1, c2) << '\n';
    return 0;
}