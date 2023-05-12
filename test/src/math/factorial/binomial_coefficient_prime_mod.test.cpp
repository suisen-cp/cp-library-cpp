#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint;

namespace atcoder {
    std::istream& operator>>(std::istream& in, mint &a) {
        long long e; in >> e; a = e;
        return in;
    }
    
    std::ostream& operator<<(std::ostream& out, const mint &a) {
        out << a.val();
        return out;
    }
} // namespace atcoder

#include "library/math/factorial.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t, m;
    std::cin >> t >> m;
    mint::set_mod(m);

    suisen::factorial<mint> fac(std::min(m - 1, 10000000));
    while (t --> 0) {
        int n, k;
        std::cin >> n >> k;
        std::cout << fac.binom(n, k) << '\n';
    }
}