#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_polynomials"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

namespace atcoder {
    std::istream& operator>>(std::istream& in, mint& a) {
        long long e; in >> e; a = e;
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const mint& a) {
        out << a.val();
        return out;
    }
} // namespace atcoder

#include "library/polynomial/formal_power_series.hpp"
#include "library/polynomial/polynomial_gcd.hpp"

using fps = suisen::FormalPowerSeries<mint>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    fps a(n), b(m);
    for (auto& e : a) std::cin >> e;
    for (auto& e : b) std::cin >> e;

    auto [x, g] = suisen::polynomial_gcd_inv(a, b);
    if (g == fps{ 1 }) {
        int T = x.size();
        std::cout << T << '\n';
        for (int i = 0; i < T; ++i) {
            std::cout << x[i];
            if (i + 1 != T) std::cout << ' ';
        }
        std::cout << '\n';
    } else {
        std::cout << -1 << '\n';
    }
}