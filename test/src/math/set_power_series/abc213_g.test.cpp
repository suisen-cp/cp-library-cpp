#define PROBLEM "https://atcoder.jp/contests/abc213/tasks/abc213_g"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/math/set_power_series.hpp"
#include "library/transform/subset.hpp"

using namespace suisen;

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> c(1 << n, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        c[(1 << u) | (1 << v)] = 1;
    }
    suisen::subset_transform::zeta(c);
    suisen::SetPowerSeries<mint> g(n);
    for (int i = 0; i < 1 << n; ++i) {
        g[i] = mint(2).pow(c[i]);
    }

    assert(g.inv() * g == suisen::SetPowerSeries<mint>::one(n));

    auto f = g.log();
    auto h = f.exp();
    // test of exp
    assert(g == h);
    std::vector<mint> ans(n, 0);
    int full = (1 << n) - 1;
    for (int i = 1; i < 1 << n; i += 2) {
        mint x = f[i] * g[full ^ i];
        for (int j = 0; j < n; ++j) ans[j] += ((i >> j) & 1) * x;
    }
    for (int i = 1; i < n; ++i) {
        std::cout << ans[i].val() << std::endl;
    }
    return 0;
}