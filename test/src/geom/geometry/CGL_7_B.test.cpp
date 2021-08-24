#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_B"
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

    Point p1, p2, p3;
    std::cin >> p1 >> p2 >> p3;
    Circle c = pI(p1, p2, p3);
    std::cout << c.center << ' ' << c.radius << '\n';
    return 0;
}