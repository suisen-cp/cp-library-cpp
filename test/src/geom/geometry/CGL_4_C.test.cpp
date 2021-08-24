#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C"

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
    std::cin >> n;

    Polygon convex(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> convex[i];
    }

    int q;
    std::cin >> q;
    while (q --> 0) {
        Point p1, p2;
        std::cin >> p1 >> p2;
        std::cout << area(convex_cut(convex, Line(p1, p2))) << '\n';
    }
    return 0;
}