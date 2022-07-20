#define PROBLEM "https://judge.yosupo.jp/problem/sharp_p_subset_sum"

#include <iostream>
#include <vector>

#include "library/polynomial/formal_power_series.hpp"
#include "library/polynomial/subset_sum.hpp"

using mint = atcoder::modint998244353;

int main() {
    int n, t;
    std::cin >> n >> t;
    std::vector<int> items(n);
    for (int &e : items) std::cin >> e;
    auto f = suisen::subset_sum<suisen::FormalPowerSeries<mint>>(t, items);
    for (int i = 1; i <= t; ++i) {
        std::cout << f[i].val() << " \n"[i == t];
    }
    return 0;
}