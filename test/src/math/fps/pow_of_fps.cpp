#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include <iostream>
#include <vector>

#include <atcoder/modint>

#include "library/math/fps.hpp"

using mint = atcoder::modint998244353;

int main() {
    int n, m;
    std::cin >> n >> m;
    suisen::FPS<mint> f(n);
    for (int i = 0; i < n; ++i) {
        int coef;
        std::cin >> coef;
        f[i] = coef;
    }
    auto g = f.pow(m, n - 1);
    for (int i = 0; i < n; ++i) {
        std::cout << g[i].val() << " \n"[i == n - 1];
    }
    return 0;
}