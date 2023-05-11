#define PROBLEM "https://atcoder.jp/contests/abc253/tasks/abc253_Ex"

#include <iostream>

#include <atcoder/modint>
using mint = atcoder::modint998244353;

#include "library/math/factorial.hpp"
#include "library/math/array_set_power_series.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector g(n, std::vector<int>(n, 0));

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        ++g[u][v], ++g[v][u];
    }

    suisen::ArraySetPowerSeries<mint, 15> f(0);
    for (int u = 0; u < n; ++u) {
        std::vector<mint> e(1 << u);
        for (int v = 0; v < u; ++v) e[1 << v] = g[u][v];
        suisen::subset_transform::zeta(e);
        auto g = f;
        for (int s = 0; s < 1 << u; ++s) g[s] *= e[s];
        f.concat(g.exp());
    }

    const auto F = f.zeta();
    const auto f2 = F.pow(2).mobius();
    const auto f4 = F.pow(4).mobius();
    const auto f6 = F.pow(6).mobius();
    const auto f7 = F.pow(7).mobius();

    auto prod = [&](const auto& a, const auto& b) {
        mint ans = 0;
        int mask = (1 << n) - 1;
        for (int s = 0; s < 1 << n; ++s) ans += a[s] * b[~s & mask];
        return ans;
    };

    auto calc = [&](int k) {
        if (k == 1) {
            return f.back();
        } else if (k == 2) {
            return f2.back();
        } else if (k == 3) {
            return prod(f, f2);
        } else if (k == 4) {
            return f4.back();
        } else if (k == 5) {
            return prod(f, f4);
        } else if (k == 6) {
            return f6.back();
        } else if (k == 7) {
            return f7.back();
        } else if (k == 8) {
            return prod(f, f7);
        } else if (k == 9) {
            return prod(f2, f7);
        } else if (k == 10) {
            return prod(f4, f6);
        } else if (k == 11) {
            return prod(f4, f7);
        } else if (k == 12) {
            return prod(f6, f6);
        } else if (k == 13) {
            return prod(f6, f7);
        }
        assert(false);
    };

    suisen::factorial<mint> fac(n);
    std::vector<mint> ans;
    for (int k = 1; k <= n - 1; ++k) {
        mint ans = fac.fac(k) * fac.fac_inv(n - k) * calc(n - k) / mint(m).pow(k);
        std::cout << ans.val() << std::endl;
    }

    return 0;
}