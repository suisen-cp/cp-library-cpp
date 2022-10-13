#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind_small_p_large_n"

#include <iostream>

#include <atcoder/modint>

using mint = atcoder::modint;

#include "library/sequence/stirling_number1_small_prime_mod.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t, p;
    std::cin >> t >> p;

    mint::set_mod(p);

    suisen::StirlingNumber1SmallPrimeMod<mint> s1;

    for (int i = 0; i < t; ++i) {
        long long n, k;
        std::cin >> n >> k;
        std::cout << (((n - k) & 1 ? -1 : 1) * s1(n, k)).val() << '\n';
    }

    return 0;
}