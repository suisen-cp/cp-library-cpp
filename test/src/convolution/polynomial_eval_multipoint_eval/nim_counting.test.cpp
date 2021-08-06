#define PROBLEM "https://atcoder.jp/contests/abc212/tasks/abc212_h"

#include <iostream>
#include <atcoder/convolution>
#include <atcoder/modint>

#include "library/transform/walsh_hadamard.hpp"
#include "library/convolution/polynomial_eval_multipoint_eval.hpp"

using mint = atcoder::modint998244353;

constexpr int M = 1 << 16;

int main() {
    suisen::FPS<mint>::set_multiplication([](const auto &f, const auto &g) { return atcoder::convolution(f, g); });

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::vector<mint> c(M, 0);
    for (int i = 0; i < k; ++i) {
        int v;
        std::cin >> v;
        ++c[v];
    }

    suisen::FPS<mint> f(n + 1, 1);
    f[0] = 0;

    auto res = suisen::polynomial_eval<mint, suisen::WalshHadamard>(c, f);

    std::cout << std::accumulate(res.begin() + 1, res.end(), mint(0)).val() << std::endl;

    return 0;
}