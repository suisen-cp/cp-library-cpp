#define PROBLEM "https://yukicoder.me/problems/no/2512"

#include "library/math/binomial_coefficient_sum.hpp"

#include <iostream>

#include <atcoder/modint>

using mint = atcoder::modint998244353;

constexpr int M = 400010;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    std::vector<std::pair<int, int>> qs(q);
    for (int i = 0; i < q; ++i) {
        int n, m;
        std::cin >> n >> m;
        qs[i] = { n, 2 * m };
    }

    const mint inv2 = mint(2).inv();
    suisen::pow_mods<mint> pw(-inv2, 200010);

    std::vector<mint> res = suisen::binom_sum_prefix<mint>(qs, -2);
    for (int i = 0; i < q; ++i) {
        auto [n, m] = qs[i];
        std::cout << ((res[i] - 1) * -pw[n + 1]).val() << '\n';
    }

    return 0;
}