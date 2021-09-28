#define PROBLEM "https://atcoder.jp/contests/abc212/tasks/abc212_h"

#include <iostream>
#include <atcoder/modint>

#include "library/transform/walsh_hadamard.hpp"
#include "library/convolution/polynomial_eval.hpp"
using namespace suisen;

using mint = atcoder::modint998244353;

constexpr int M = 1 << 16;

int main() {
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

    using namespace walsh_hadamard;

    auto res = suisen::polynomial_eval<mint, walsh_hadamard<mint>, walsh_hadamard_inv<mint>>(c, [n](mint x) {
        return x == 1 ? n : x * (x.pow(n) - 1) / (x - 1);
        });

    std::cout << std::accumulate(res.begin() + 1, res.end(), mint(0)).val() << std::endl;

    return 0;
}