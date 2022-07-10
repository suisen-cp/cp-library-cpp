#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0585"

#include <cassert>
#include <iostream>
#include <iomanip>

#include "library/integral_geom/closest_pair.hpp"

using namespace suisen::integral_geometry;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(20);

    int n;
    std::cin >> n;

    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> points[i];
    }

    auto [p, q] = closest_pair(points);
    std::cout << square_abs(p - q) << '\n';

    return 0;
}