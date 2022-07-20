#define PROBLEM "https://atcoder.jp/contests/abc212/tasks/abc212_h"

#include <iostream>
#include <atcoder/convolution>
#include <atcoder/modint>

#include "library/polynomial/fps.hpp"
#include "library/transform/walsh_hadamard.hpp"
#include "library/convolution/polynomial_eval_multipoint_eval.hpp"
using namespace suisen;

using mint = atcoder::modint998244353;

constexpr int M = 1 << 16;

int main() {
    FPS<mint>::set_multiplication([](const auto& f, const auto& g) { return atcoder::convolution(f, g); });

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

    FPS<mint> f(n + 1, 1);
    f[0] = 0;

    using namespace walsh_hadamard_transform;

    auto res = polynomial_eval<mint, walsh_hadamard<mint>, walsh_hadamard_inv<mint>>(c, f);

    std::cout << std::accumulate(res.begin() + 1, res.end(), mint(0)).val() << std::endl;

    return 0;
}