#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B"
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

    int n;
    std::cin >> n;

    Polygon poly(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> poly[i];
    }

    auto [i, j, diam] = convex_diameter(poly);
    std::cout << diam << '\n';
    return 0;
}