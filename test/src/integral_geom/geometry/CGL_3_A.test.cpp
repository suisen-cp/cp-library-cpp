#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A"

#include <cassert>
#include <iostream>
#include <iomanip>

#include "library/integral_geom/geometry.hpp"

using namespace suisen::integral_geometry;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(1);

    int n;
    std::cin >> n;

    Polygon poly(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> poly[i];
    }
    std::cout << std::fixed << std::setprecision(1) << area_doubled(poly) / 2. << '\n';
    return 0;
}