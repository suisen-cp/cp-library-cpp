#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C"

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

    int q;
    std::cin >> q;

    while (q --> 0) {
        Point p;
        std::cin >> p;
        Containment c = contains(poly, p);
        if (c == Containment::IN) {
            std::cout << 2 << '\n';
        } else if (c == Containment::ON) {
            std::cout << 1 << '\n';
        } else {
            std::cout << 0 << '\n';
        }
    }
    return 0;
}