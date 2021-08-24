#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_F"
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

    Point p, pc;
    coordinate_t rc;
    std::cin >> p >> pc >> rc;
    Circle c(pc, rc);

    auto v = tangent_to_circle(c, p);
    std::sort(v.begin(), v.end(), XY_COMPARATOR);
    std::cout << v[0] << '\n' << v[1] << '\n';
    return 0;
}