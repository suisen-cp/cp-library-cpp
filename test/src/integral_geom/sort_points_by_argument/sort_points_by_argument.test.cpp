#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include <iostream>

#include "library/integral_geom/sort_points_by_argument.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> points(n);
    for (auto &[x, y] : points) std::cin >> x >> y;
    
    suisen::integral_geometry::sort_points_by_argument(points);

    for (auto &[x, y] : points) {
        std::cout << x << ' ' << y << '\n';
    }
    return 0;
}