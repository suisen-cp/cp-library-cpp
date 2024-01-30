#define PROBLEM "https://judge.yosupo.jp/problem/static_range_mode_query"

#include "library/range_query/static_range_mode_query.hpp"

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;

    suisen::StaticRangeModeQuery range_mode(a);
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        auto [val, num] = range_mode(l, r);
        std::cout << val << ' ' << num << '\n';
    }
}