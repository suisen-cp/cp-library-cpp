#define PROBLEM "https://atcoder.jp/contests/dp/tasks/dp_v"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint;

#include "library/tree/rerooting.hpp"

using DP = std::array<mint, 2>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    mint::set_mod(m);

    suisen::Rerooting g(n);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        g.add_edge(u, v);
    }

    std::vector ans = g.run_dp(
        [](const DP& x, const DP& y) {
            return DP{ x[0] * y[0], (x[0] + x[1]) * (y[0] + y[1]) - (x[0] * y[0]) };
        },
        []() {
            return DP{ 1, 0 };
        },
        [](const DP& x) {
            return DP{ x[0], x[0] + x[1] };
        },
        [](const DP& x) {
            return DP{ x[0], x[0] + x[1] };
        }
    );

    for (const DP& v : ans) {
        std::cout << v[1].val() << '\n';
    }
}