#define PROBLEM "https://judge.yosupo.jp/problem/sharp_p_subset_sum"

#include <iostream>
#include <vector>

#include <atcoder/modint>
#include <atcoder/convolution>

#include "library/polynomial/subset_sum.hpp"

using mint = atcoder::modint998244353;

int main() {
    suisen::FPS<mint>::set_multiplication([](const auto &a, const auto &b) { return atcoder::convolution(a, b); });

    int n, t;
    std::cin >> n >> t;
    std::vector<int> items(n);
    for (int &e : items) std::cin >> e;
    auto f = suisen::subset_sum<mint>(t, items);
    for (int i = 1; i <= t; ++i) {
        std::cout << f[i].val() << " \n"[i == t];
    }
    return 0;
}