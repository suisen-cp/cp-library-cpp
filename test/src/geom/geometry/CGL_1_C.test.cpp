#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C"

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

    int q;
    std::cin >> q;
    while (q --> 0) {
        Point p3;
        std::cin >> p3;
        int dir = isp(p1, p2, p3);
        if (dir == ISP::BACK) {
            std::cout << "ONLINE_BACK" << '\n';
        } else if (dir == ISP::FRONT) {
            std::cout << "ONLINE_FRONT" << '\n';
        } else if (dir == ISP::MIDDLE) {
            std::cout << "ON_SEGMENT" << '\n';
        } else if (dir == ISP::L_CURVE) {
            std::cout << "COUNTER_CLOCKWISE" << '\n';
        } else if (dir == ISP::R_CURVE) {
            std::cout << "CLOCKWISE" << '\n';
        }
    }
    return 0;
}