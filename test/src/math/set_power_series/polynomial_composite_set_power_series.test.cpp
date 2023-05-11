#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_composite_set_power_series"

#include <iostream>

#include "library/math/set_power_series.hpp"

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

using suisen::SetPowerSeries;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m, n;
    std::cin >> m >> n;

    std::vector<mint> f(m), g(1 << n);
    for (auto &e : f) std::cin >> e;
    for (auto &e : g) std::cin >> e;
    
    std::vector<mint> fg = suisen::SetPowerSeries<mint>::polynomial_composite(f, g);
    for (auto &e : fg) std::cout << e << ' ';
    std::cout << '\n';
    return 0;
}