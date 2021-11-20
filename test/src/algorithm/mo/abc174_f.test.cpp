#define PROBLEM "https://atcoder.jp/contests/abc174/tasks/abc174_f"

#include <iostream>

#include "library/algorithm/mo.hpp"
using suisen::Mo;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<int> c(n);
    for (int &e : c) {
        std::cin >> e;
        --e;
    }
    std::vector<std::pair<int, int>> queries(q);
    for (auto &[l, r] : queries) {
        std::cin >> l >> r;
        --l;
    }

    std::vector<int> cnt(n, 0);
    int ans = 0;

    auto res = Mo(n, queries).solve(
        [&]{ return ans; },
        [&](int i) { if (++cnt[c[i]] == 1) ++ans; },
        [&](int i) { if (--cnt[c[i]] == 0) --ans; }
    );

    for (auto x : res) std::cout << x << '\n';
    return 0;
}