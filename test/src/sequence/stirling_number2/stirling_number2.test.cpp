#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind"

#include <iostream>
#include <atcoder/modint>
#include <atcoder/convolution>

#include "library/polynomial/fps.hpp"
#include "library/sequence/stirling_number2.hpp"

using mint = atcoder::modint998244353;

int main() {
    suisen::FPS<mint>::set_multiplication([](const auto &a, const auto &b) { return atcoder::convolution(a, b); });

    int n;
    std::cin >> n;
    auto ans = suisen::stirling_number2<suisen::FPS<mint>>(n);
    for (int i = 0; i <= n; ++i) {
        std::cout << ans[i].val() << " \n"[i == n];
    }
    return 0;
}