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

    suisen::ArraySetPowerSeries<mint, 15> t(0);
    for (int u = 0; u < n; ++u) {
        std::vector<mint> e(1 << u);
        for (int v = 0; v < u; ++v) e[1 << v] = g[u][v];
        suisen::subset_transform::zeta(e);
        auto g = t;
        for (int s = 0; s < 1 << u; ++s) g[s] *= e[s];
        t.concat(g.exp());
    }

    suisen::ArraySetPowerSeries<suisen::ArrayFPSNaive<mint, 15>, 15> f(n);
    for (int s = 1; s < 1 << n; ++s) {
        f[s][1] = t[s];
    }

    suisen::factorial<mint> fac(n);

    auto exp_f = f.exp().back();

    for (int k = 1; k < n; ++k) {
        std::cout << (fac.fac(k) * exp_f[n - k] / mint(m).pow(k)).val() << std::endl;
    }

    return 0;
}

