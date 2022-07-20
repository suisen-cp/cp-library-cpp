#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

#include <iostream>

#include "library/polynomial/formal_power_series.hpp"
#include "library/polynomial/bostan_mori.hpp"
using suisen::FormalPowerSeries;

using mint = atcoder::modint998244353;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t d;
    unsigned long long k;
    std::cin >> d >> k;

    FormalPowerSeries<mint> a(d), c(d);
    for (std::size_t i = 0; i < d; ++i) {
        unsigned int v;
        std::cin >> v;
        a[i] = v;
    }
    for (std::size_t i = 0; i < d; ++i) {
        unsigned int v;
        std::cin >> v;
        c[i] = v;
    }
    
    std::cout << suisen::nth_term_of_linearly_recurrent_sequence(a, c, k).val() << std::endl;
    
    return 0;
}