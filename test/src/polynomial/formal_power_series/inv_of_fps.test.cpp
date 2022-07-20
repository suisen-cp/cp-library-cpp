#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

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
    auto inv_f = f.inv();
    for (int i = 0; i < n; ++i) {
        std::cout << inv_f[i].val() << " \n"[i == n - 1];
    }
    return 0;
}