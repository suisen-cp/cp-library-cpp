#define PROBLEM "https://judge.yosupo.jp/problem/product_of_polynomial_sequence"

#include <iostream>
#include <atcoder/modint>
#include <atcoder/convolution>

using mint = atcoder::modint998244353;

#include "library/polynomial/formal_power_series.hpp"
using suisen::FormalPowerSeries;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<FormalPowerSeries<mint>> fs(n);
    for (int i = 0; i < n; ++i) {
        int d;
        std::cin >> d;
        fs[i].resize(d + 1);
        for (int j = 0, v; j <= d; ++j) {
            std::cin >> v, fs[i][j] = v;
        }
    }
    FormalPowerSeries<mint> g = FormalPowerSeries<mint>::prod(fs);
    const int m = g.size();
    for (int i = 0; i < m; ++i) {
        std::cout << g[i].val();
        if (i + 1 < m) std::cout << ' ';
    }
    std::cout << '\n';
    return 0;
}