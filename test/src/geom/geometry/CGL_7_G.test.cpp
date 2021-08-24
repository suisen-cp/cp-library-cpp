#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_G"
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

    Point p1, p2;
    coordinate_t r1, r2;
    std::cin >> p1 >> r1 >> p2 >> r2;
    Circle c1(p1, r1), c2(p2, r2);

    auto v = common_tangent(c1, c2);
    std::sort(v.begin(), v.end(), [](auto &l1, auto &l2) { return XY_COMPARATOR(l1.a, l2.a); });
    for (auto [p, q] : v) {
        std::cout << p << '\n';
    }
    return 0;
}