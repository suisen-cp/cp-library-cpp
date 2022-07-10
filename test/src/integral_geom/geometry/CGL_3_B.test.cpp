#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B"

#include <cassert>
#include <iostream>
#include <iomanip>

#include "library/integral_geom/geometry.hpp"

using namespace suisen::integral_geometry;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(20);

    int n;
    std::cin >> n;

    Polygon poly(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> poly[i];
    }
    std::cout << int(is_convex(poly)) << '\n';
    return 0;
}