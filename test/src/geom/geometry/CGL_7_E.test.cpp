#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E"
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

    auto v = common_point(c1, c2);
    if (v.size() == 1) v.push_back(v[0]);
    std::sort(v.begin(), v.end(), XY_COMPARATOR);
    std::cout << v[0] << ' ' << v[1] << '\n';
    return 0;
}