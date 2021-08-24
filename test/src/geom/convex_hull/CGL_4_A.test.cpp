#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A"

#include <cassert>
#include <iostream>
#include <iomanip>

#include "library/geom/geometry.hpp"
#include "library/geom/convex_hull.hpp"

using namespace suisen::geometry;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(0);

    int n;
    std::cin >> n;

    std::vector<Point> points(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> points[i];
    }

    std::vector<int> ids = convex_hull(points);

    int amin = 0;
    for (int i = 1; i < int(ids.size()); ++i) {
        coordinate_t x0 = points[ids[amin]].real(), y0 = points[ids[amin]].imag();
        coordinate_t x1 = points[ids[i]].real(), y1 = points[ids[i]].imag();
        if (y1 < y0 or (y1 == y0 and x1 < x0)) {
            amin = i;
        }
    }

    std::cout << ids.size() << '\n';
    for (int i = 0; i < int(ids.size()); ++i) {
        std::cout << points[ids[(amin + i) % ids.size()]] << '\n';
    }
    return 0;
}