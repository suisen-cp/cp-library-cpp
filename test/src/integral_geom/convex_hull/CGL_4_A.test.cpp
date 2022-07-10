#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A"

#include <cassert>
#include <iostream>
#include <iomanip>

#include "library/integral_geom/convex_hull.hpp"

using namespace suisen::integral_geometry;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(0);

    int n;
    std::cin >> n;

    std::vector<std::pair<long long, long long>> points(n);

    for (auto &[x, y] : points) std::cin >> x >> y;

    std::vector<int> ids = convex_hull(points);

    int amin = 0;
    for (int i = 1; i < int(ids.size()); ++i) {
        long long x0 = points[ids[amin]].first, y0 = points[ids[amin]].second;
        long long x1 = points[ids[i]].first, y1 = points[ids[i]].second;
        if (y1 < y0 or (y1 == y0 and x1 < x0)) {
            amin = i;
        }
    }

    std::cout << ids.size() << '\n';
    for (int i = 0; i < int(ids.size()); ++i) {
        auto [x, y] = points[ids[(amin + i) % ids.size()]];
        std::cout << x << ' ' << y << '\n';
    }
    return 0;
}