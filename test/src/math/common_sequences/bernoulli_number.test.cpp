#define PROBLEM "https://judge.yosupo.jp/problem/bernoulli_number"

#include <iostream>

#include <atcoder/modint>
#include <atcoder/convolution>

#include "library/math/common_sequences.hpp"

using mint = atcoder::modint998244353;

int main() {
    suisen::FPS<mint>::set_multiplication([](const auto &a, const auto &b) { return atcoder::convolution(a, b); });

    int n;
    std::cin >> n;
    auto f = suisen::bernoulli_number<mint>(n);
    for (int i = 0; i <= n; ++i) {
        std::cout << f[i].val() << " \n"[i == n];
    }
    return 0;
}