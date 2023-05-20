#define PROBLEM "https://judge.yosupo.jp/problem/conversion_from_monomial_basis_to_newton_basis"

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

#include "library/polynomial/formal_power_series.hpp"
#include "library/polynomial/convert_to_newton_basis.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    suisen::FormalPowerSeries<mint> f(n);
    for (auto &e : f) std::cin >> e;
    std::vector<mint> p(n);
    for (auto &e : p) std::cin >> e;

    std::vector<mint> b = suisen::convert_to_newton_basis(f, p);
    for (int i = 0; i < n; ++i) {
        std::cout << b[i];
        if (i + 1 != n) std::cout << ' ';
    }
    std::cout << '\n';
}