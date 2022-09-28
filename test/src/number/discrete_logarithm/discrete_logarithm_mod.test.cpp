#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint;

#include "library/number/discrete_logarithm.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t --> 0) {
        int x, y, m;
        std::cin >> x >> y >> m;
        mint::set_mod(m);
        std::cout << suisen::discrete_logarithm<mint>(x, y) << '\n';
    }

    return 0;
}