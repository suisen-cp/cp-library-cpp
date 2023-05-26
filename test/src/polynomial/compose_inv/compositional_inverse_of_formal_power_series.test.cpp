#define PROBLEM "https://judge.yosupo.jp/problem/compositional_inverse_of_formal_power_series"

#include <iostream>

#include <atcoder/modint>

using mint = atcoder::modint998244353;

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

#include "library/polynomial/compose_inv.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    
    std::vector<mint> a(n);
    for (auto &e : a) std::cin >> e;

    std::vector<mint> b = suisen::compositional_inv(a, n);
    for (auto &e : b) std::cout << e << ' ';
    std::cout << '\n';
}