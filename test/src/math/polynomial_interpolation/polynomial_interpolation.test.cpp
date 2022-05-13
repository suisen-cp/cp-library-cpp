#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include <iostream>
#include <atcoder/modint>
#include <atcoder/convolution>

#include "library/math/polynomial_interpolation.hpp"

using mint = atcoder::modint998244353;

int main() {
    suisen::FPS<mint>::set_multiplication([](const auto &a, const auto &b) { return atcoder::convolution(a, b); });
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
    auto f = suisen::polynomial_interpolation(x, y);
    for (int i = 0; i < n; ++i) {
        std::cout << f[i].val() << " \n"[i == n - 1];
    }
    return 0;
}