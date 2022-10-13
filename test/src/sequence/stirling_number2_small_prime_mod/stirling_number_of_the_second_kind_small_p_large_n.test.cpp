#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind_small_p_large_n"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint;

#include "library/sequence/stirling_number2_small_prime_mod.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t, p;
    std::cin >> t >> p;
    mint::set_mod(p);

    suisen::StirlingNumber2SmallPrimeMod<mint> s2;

    while (t --> 0) {
        long long n, k;
        std::cin >> n >> k;
        std::cout << s2(n, k).val() << '\n';
    }

    return 0;
}