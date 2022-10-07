#define PROBLEM "https://yukicoder.me/problems/no/2097"

#include <iostream>

#include <atcoder/modint>

#include "library/math/factorial.hpp"
#include "library/polynomial/formal_power_series.hpp"
#include "library/polynomial/prod_f(r^k_x).hpp"

using mint = atcoder::modint998244353;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, l;
    std::cin >> n >> m >> l;

    suisen::factorial<mint> fac(l);

    suisen::FormalPowerSeries<mint> f(l + 1);
    f[0] = mint(2).pow(n);
    for (int i = 1; i <= l; ++i) {
        f[i] = fac.fac_inv(i);
    }

    f = prod_f_rk_x(f, 2, m);

    for (int i = 1; i <= l; ++i) {
        std::cout << (f[i] * fac.fac(i)).val() << '\n';
    }
}