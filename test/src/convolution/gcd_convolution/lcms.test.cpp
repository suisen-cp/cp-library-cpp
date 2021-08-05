#define PROBLEM "https://atcoder.jp/contests/agc038/tasks/agc038_c"

#include <iostream>
#include <atcoder/modint>

#include "library/convolution/gcd_convolution.hpp"

using mint = atcoder::modint998244353;

constexpr int M = 1000000;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<mint> count(M + 1, 0);
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        ++count[v];
    }

    std::vector<mint> f(M + 1);
    for (int i = 0; i <= M; ++i) f[i] = count[i] * i;

    auto c = suisen::gcd_convolution<mint>(f, f);

    mint ans = 0;
    for (int g = 1; g <= M; ++g) {
        ans += (c[g] - f[g] * f[g]) / (2 * g);
    }

    for (int i = 1; i <= M; ++i) {
        ans += count[i] * (count[i] - 1) * i / 2;
    }
    std::cout << ans.val() << std::endl;
    return 0;
}