#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind"

#include <iostream>
#include <atcoder/modint>
#include <atcoder/convolution>

#include "library/polynomial/formal_power_series.hpp"
#include "library/sequence/stirling_number1.hpp"

using mint = atcoder::modint998244353;

int main() {
    int n;
    std::cin >> n;
    auto ans = suisen::stirling_number1<suisen::FormalPowerSeries<mint>>(n);
    for (int i = 0; i <= n; ++i) {
        std::cout << ((n - i) & 1 ? -ans[i] : ans[i]).val() << " \n"[i == n];
    }
    return 0;
}