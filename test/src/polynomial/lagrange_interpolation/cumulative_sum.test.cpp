#define PROBLEM "https://atcoder.jp/contests/abc208/tasks/abc208_f"

#include <iostream>
#include <atcoder/modint>

#include "library/polynomial/lagrange_interpolation.hpp"
#include "library/number/linear_sieve.hpp"

using mint = atcoder::modint1000000007;

int main() {
    long long n;
    int m, k;
    std::cin >> n >> m >> k;
    const auto mpf = suisen::LinearSieve(k + m).get_min_prime_factor();
    std::vector<mint> f(k + m + 1);
    for (int i = 1; i <= k + m; ++i) {
        if (i == 1) {
            f[i] = 1;
        } else if (mpf[i] == i) {
            f[i] = mint(i).pow(k);
        } else {
            f[i] = f[mpf[i]] * f[i / mpf[i]];
        }
    }
    for (int loop = 0; loop < m; ++loop) {
        for (int i = 1; i <= k + m; ++i) {
            f[i] += f[i - 1];
        }
    }
    std::cout << suisen::lagrange_interpolation_arithmetic_progression<mint>(f, n).val() << '\n';
    return 0;
}
