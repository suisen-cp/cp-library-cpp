#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind"

#include <iostream>
#include <atcoder/modint>
#include <atcoder/convolution>

#include "library/polynomial/common_sequences.hpp"

using mint = atcoder::modint998244353;

int main() {
    suisen::FPS<mint>::set_multiplication([](const auto &a, const auto &b) { return atcoder::convolution(a, b); });

    int n;
    std::cin >> n;
    auto ans = suisen::stirling_number1<mint>(n);
    for (int i = 0; i <= n; ++i) {
        std::cout << ((n - i) & 1 ? -ans[i] : ans[i]).val() << " \n"[i == n];
    }
    return 0;
}