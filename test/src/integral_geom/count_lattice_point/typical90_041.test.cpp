#define PROBLEM "https://atcoder.jp/contests/typical90/tasks/typical90_041"

#include <iostream>

#include "library/integral_geom/convex_hull.hpp"
#include "library/integral_geom/count_lattice_point.hpp"
using namespace suisen::integral_geometry;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::pair<long long, long long>> points(n);
    for (auto &[x, y] : points) std::cin >> x >> y;

    std::vector<std::pair<long long, long long>> ch;
    for (int id : convex_hull(points)) {
        ch.push_back(points[id]);
    }
    std::cout << count_lattice_points(ch) - n << std::endl;

    return 0;
}