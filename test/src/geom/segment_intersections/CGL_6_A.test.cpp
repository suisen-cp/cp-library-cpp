#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_6_A"

#include <iostream>

#include "library/geom/segment_intersections.hpp"

using namespace suisen::geometry;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::pair<int, std::pair<int, int>>> v;
    std::vector<std::pair<std::pair<int, int>, int>> h;
    for (int i = 0; i < n; ++i) {
        int x0, y0, x1, y1;
        std::cin >> x0 >> y0 >> x1 >> y1;
        if (x0 == x1) {
            v.emplace_back(x0, std::make_pair(y0, y1));
        } else {
            h.emplace_back(std::make_pair(x0, x1), y0);
        }
    }
    long long ans = segment_intersections(v, h);
    std::cout << ans << '\n';
    return 0;
}