#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"

#include <iostream>
#include <vector>

#include <atcoder/modint>
#include <atcoder/convolution>

#include "library/polynomial/formal_power_series.hpp"

using mint = atcoder::modint998244353;

int main() {
    int n;
    std::cin >> n;
    suisen::FormalPowerSeries<mint> f(n);
    for (int i = 0; i < n; ++i) {
        int coef;
        std::cin >> coef;
        f[i] = coef;
    }
    auto opt_g = f.safe_sqrt();
    if (not opt_g.has_value()) {
        std::cout << -1 << std::endl;
        return 0;
    }
    auto g = std::move(*opt_g);
    for (int i = 0; i < n; ++i) {
        std::cout << g[i].val() << " \n"[i == n - 1];
    }
    return 0;
}