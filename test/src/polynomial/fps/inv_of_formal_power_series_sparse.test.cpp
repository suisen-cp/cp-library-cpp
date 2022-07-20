#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series_sparse"

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
    auto inv_f = f.inv();
    for (int i = 0; i < n; ++i) {
        std::cout << inv_f[i].val() << " \n"[i == n - 1];
    }
    return 0;
}