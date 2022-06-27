#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series_sparse"

#include <iostream>
#include <vector>

#include <atcoder/modint>

#include "library/polynomial/fps.hpp"

using mint = atcoder::modint998244353;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    suisen::FPS<mint> f(n);
    for (int i = 0; i < k; ++i) {
        int d, v;
        std::cin >> d >> v;
        f[d] = v;
    }
    auto opt_sqrt_f = f.optional_sqrt(n - 1);
    if (not opt_sqrt_f.has_value()) {
        std::cout << -1 << std::endl;
        return 0;
    }
    auto sqrt_f = std::move(*opt_sqrt_f);
    for (int i = 0; i < n; ++i) {
        std::cout << sqrt_f[i].val() << " \n"[i == n - 1];
    }
    return 0;
}