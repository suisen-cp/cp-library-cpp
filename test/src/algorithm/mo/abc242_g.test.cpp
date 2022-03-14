#define PROBLEM "https://atcoder.jp/contests/abc242/tasks/abc242_g"

#include <iostream>

#include "library/algorithm/mo.hpp"
using suisen::Mo;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (auto& e : a) std::cin >> e, --e;

    int q;
    std::cin >> q;

    std::vector<std::pair<int, int>> qs;
    for (int i = 0; i < q; ++i) {
        int l, r;
        std::cin >> l >> r;
        --l;
        qs.emplace_back(l, r);
    }

    std::vector<int8_t> cnt(n);
    int cur = 0;

    auto ans = Mo(n, qs).solve(
        [&] {
            return cur;
        },
        [&](int i) {
            auto &v = cnt[a[i]];
            cur += v, v ^= 1;
        },
        [&](int i) {
            auto &v = cnt[a[i]];
            v ^= 1, cur -= v;
        }
    );

    for (int e : ans) std::cout << e << '\n';

    return 0;
}