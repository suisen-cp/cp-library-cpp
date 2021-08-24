#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D"
#define ERROR 0.00000001

#include <cassert>
#include <iostream>
#include <iomanip>

#include "library/geom/geometry.hpp"

using namespace suisen::geometry;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(20);

    int q;
    std::cin >> q;
    while (q --> 0) {
        Point p1, p2, p3, p4;
        std::cin >> p1 >> p2 >> p3 >> p4;
        Segment l1(p1, p2), l2(p3, p4);
        std::cout << distance(l1, l2) << '\n';
    }
    return 0;
}