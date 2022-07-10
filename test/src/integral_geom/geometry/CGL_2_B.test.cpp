#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B"

#include <iostream>
#include <iomanip>

#include "library/integral_geom/geometry.hpp"

using namespace suisen::integral_geometry;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;
    while (q --> 0) {
        Point p1, p2, p3, p4;
        std::cin >> p1 >> p2 >> p3 >> p4;
        Segment l1(p1, p2), l2(p3, p4);
        if (has_common_point(l1, l2)) {
            std::cout << 1 << '\n';
        } else {
            std::cout << 0 << '\n';
        }
    }
    return 0;
}