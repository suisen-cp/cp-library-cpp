#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include <iostream>
#include <vector>

#include <atcoder/modint>
#include <atcoder/convolution>

#include "library/polynomial/formal_power_series.hpp"
#include "library/polynomial/polynomial_taylor_shift.hpp"

using mint = atcoder::modint998244353;

int main() {
    int n, c;
    std::cin >> n >> c;
    suisen::FormalPowerSeries<mint> f(n);
    for (int i = 0; i < n; ++i) {
        int coef;
        std::cin >> coef;
        f[i] = coef;
    }
    auto g = suisen::translate(f, mint(c));
    for (int i = 0; i < n; ++i) {
        std::cout << g[i].val() << " \n"[i == n - 1];
    }
    return 0;
}