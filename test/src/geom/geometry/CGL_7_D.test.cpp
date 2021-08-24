#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D"
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

    Point center;
    coordinate_t radius;
    std::cin >> center >> radius;
    Circle circle(center, radius);

    int q;
    std::cin >> q;
    while (q --> 0) {
        Point a, b;
        std::cin >> a >> b;
        auto v = common_point(circle, Line(a, b));
        if (v.size() == 1) v.push_back(v[0]);
        std::sort(v.begin(), v.end(), XY_COMPARATOR);
        std::cout << v[0] << ' ' << v[1] << '\n';
    }
    return 0;
}