#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B"
#define ERROR 0.00000001

#include <iostream>
#include <iomanip>

#include "library/geom/geometry.hpp"

using namespace suisen::geometry;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(20);

    Point p1, p2;
    std::cin >> p1 >> p2;
    Line l(p1, p2);

    int q;
    std::cin >> q;
    while (q --> 0) {
        Point p;
        std::cin >> p;
        std::cout << reflection(p, l) << '\n';
    }
    return 0;
}