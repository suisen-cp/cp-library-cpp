#define PROBLEM "https://atcoder.jp/contests/abc208/tasks/abc208_f"

#include <iostream>
#include <atcoder/modint>

#include "library/polynomial/lagrange_interpolation.hpp"
#include "library/sequence/powers.hpp"

using mint = atcoder::modint1000000007;

int main() {
    long long n;
    int m, k;
    std::cin >> n >> m >> k;

    std::vector<mint> f = suisen::powers<mint>(k + m, k);
    for (int loop = 0; loop < m; ++loop) {
        for (int i = 1; i <= k + m; ++i) f[i] += f[i - 1];
    }

    std::cout << suisen::lagrange_interpolation_arithmetic_progression<mint>(f, n).val() << '\n';

    return 0;
}
