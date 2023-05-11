#define PROBLEM "https://atcoder.jp/contests/abc160/tasks/abc160_f"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint1000000007;

#include "library/tree/rerooting_invertible.hpp"

using DP = std::pair<mint, int>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    suisen::RerootingInvertible g(n);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        g.add_edge(u, v);
    }

    std::vector<mint> fac(n + 1), fac_inv(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i;
    fac_inv[n] = fac[n].inv();
    for (int i = n; i >= 1; --i) fac_inv[i - 1] = fac_inv[i] * i;
    auto inv = [&](int i) {
        return fac_inv[i] * fac[i - 1];
    };

    std::vector ans = g.run_dp(
        [](const DP& x, const DP& y) {
            return DP{ x.first * y.first, x.second + y.second };
        },
        []() {
            return DP{ 1, 0 };
        },
        [](const DP& x) {
            return DP{ x.first.inv(), -x.second };
        },
        [&](const DP& x) {
            return DP{ x.first * inv(x.second + 1) , x.second + 1 };
        },
        [&](const DP& x) {
            return DP{ x.first * inv(x.second + 1) , x.second + 1 };
        }
    );

    for (const DP& v : ans) {
        std::cout << (fac[n] * v.first).val() << '\n';
    }
}