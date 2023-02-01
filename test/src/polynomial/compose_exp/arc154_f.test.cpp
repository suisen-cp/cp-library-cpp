#define PROBLEM "https://atcoder.jp/contests/arc154/tasks/arc154_f"

#include <iostream>

#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/math/factorial.hpp"
#include "library/math/pow_mods.hpp"
#include "library/polynomial/formal_power_series.hpp"
#include "library/polynomial/rational_fps.hpp"
#include "library/polynomial/compose_exp.hpp"

using fps = suisen::FormalPowerSeries<mint>;
using rational_fps = suisen::RationalFPS<fps>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<fps> dens(n);
    for (int i = 0; i < n; ++i) {
        dens[i] = { n, -(n - (i + 1)) };
    }
 
    suisen::factorial<mint> fac(m);
    suisen::pow_mods<mint> pow_n(n, m);
 
    fps f(m + 1);
    for (int i = 0; i <= m; ++i) {
        f[i] = fac.fac(n) * fac.fac_inv(i) * pow_n[i];
    }
    fps g = suisen::compose_exp(fps::prod(dens), m + 1);
    
    fps h = rational_fps(f, g).to_fps(m + 1);
 
    for (int i = 1; i <= m; ++i) {
        std::cout << (h[i] * fac.fac(i)).val() << '\n';
    }
 
    return 0;
}