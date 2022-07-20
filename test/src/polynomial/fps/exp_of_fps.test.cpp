#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include <iostream>
#include <vector>

#include <atcoder/modint>
#include <atcoder/convolution>

#include "library/polynomial/fps.hpp"

using mint = atcoder::modint998244353;

int main() {
    suisen::FPS<mint>::set_multiplication([](const auto &a, const auto &b) { return atcoder::convolution(a, b); });

    int n;
    std::cin >> n;
    suisen::FPS<mint> f(n);
    for (int i = 0; i < n; ++i) {
        int coef;
        std::cin >> coef;
        f[i] = coef;
    }
    auto g = f.exp();
    for (int i = 0; i < n; ++i) {
        std::cout << g[i].val() << " \n"[i == n - 1];
    }
    return 0;
}