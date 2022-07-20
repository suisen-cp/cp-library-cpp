#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include <iostream>
#include <atcoder/modint>
#include <atcoder/convolution>

#include "library/polynomial/formal_power_series.hpp"
#include "library/polynomial/polynomial_interpolation.hpp"

using mint = atcoder::modint998244353;

int main() {
    int n;
    std::cin >> n;
    std::vector<mint> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        int xi;
        std::cin >> xi;
        x[i] = xi;
    }
    for (int i = 0; i < n; ++i) {
        int yi;
        std::cin >> yi;
        y[i] = yi;
    }
    auto f = suisen::polynomial_interpolation<suisen::FormalPowerSeries<mint>>(x, y);
    for (int i = 0; i < n; ++i) {
        std::cout << f[i].val() << " \n"[i == n - 1];
    }
    return 0;
}