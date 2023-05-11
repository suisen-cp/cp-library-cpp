#define PROBLEM "https://atcoder.jp/contests/abc236/tasks/abc236_Ex"

#include <iostream>

#include <atcoder/modint>
using mint = atcoder::modint998244353;

#include "library/math/set_power_series.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    uint64_t m;
    std::cin >> n >> m;
    std::vector<uint64_t> d(n);
    for (auto& e : d) std::cin >> e;

    std::vector<mint> h(n + 1);
    mint fac = 1;
    for (std::size_t i = 1; i <= n; ++i) {
        h[i] = (i & 1) ? fac : -fac;
        fac *= i;
    }

    std::vector<uint64_t> lcm(1 << n, 1);

    suisen::SetPowerSeries<mint> f(n);
    for (std::size_t s = 1; s < 1U << n; ++s) {
        std::size_t i = __builtin_ctz(s);
        std::size_t t = s ^ (1U << i);
        uint64_t x = d[i] / std::gcd(d[i], lcm[t]);
        lcm[s] = x > m / lcm[t] ? m + 1 : x * lcm[t];
        std::size_t pc = __builtin_popcount(s);
        f[s] = (m / lcm[s]) * h[pc];
    }

    std::cout << f.exp().back().val() << std::endl;
    return 0;
}