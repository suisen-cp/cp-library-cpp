#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_set_power_series"

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

    int n;
    std::cin >> n;

    suisen::SetPowerSeries<mint> f(n);
    for (auto &e : f) std::cin >> e;
    
    for (auto &e : f.exp()) std::cout << e << ' ';
    std::cout << '\n';
    return 0;
}