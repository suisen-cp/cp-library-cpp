#define PROBLEM "https://judge.yosupo.jp/problem/area_of_union_of_rectangles"

#include <iostream>

#include "library/algorithm/area_of_union_of_rectangles.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::tuple<long long, long long, long long, long long>> rects(n);
    for (auto &[l, r, d, u] : rects) {
        std::cin >> l >> d >> r >> u;
    }

    std::cout << suisen::area_of_union_of_rectangles(rects) << std::endl;

    return 0;
}