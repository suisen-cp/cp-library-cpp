#define PROBLEM "https://atcoder.jp/contests/abc206/tasks/abc206_e"

#include <cassert>
#include <iostream>

#include "library/transform/multiple.hpp"
#include "library/transform/divisor.hpp"
#include "library/number/sieve_of_eratosthenes.hpp"
using namespace suisen;

const Sieve<1000000> sieve;

// count l <= x, y <= r s.t. gcd(x, y) = 1
long long count_coprime_pairs(int l, int r) {
    std::vector<long long> f(r + 1, 0);
    for (int g = 1; g <= r; ++g) {
        long long w = r / g - (l + g - 1) / g + 1;
        f[g] = w * w;
    }
    std::vector<long long> f_copy = f;
    multiple_transform::mobius(f);
    long long ret = f[1];
    {
        {
            multiple_transform::zeta(f);
            assert(f == f_copy);
            multiple_transform::mobius(f);
            f_copy = f;
        }
        std::vector<long long> div_cum_naive(r + 1, 0);
        for (int g = 1; g <= r; ++g) {
            for (int d : sieve.divisors(g)) {
                div_cum_naive[g] += f[d];
            }
        }
        divisor_transform::zeta(f);
        assert(f == div_cum_naive);
        divisor_transform::mobius(f);
        assert(f == f_copy);
    }
    return ret;
}

int main() {
    int l, r;
    std::cin >> l >> r;

    long long whole = (long long) (r - l + 1) * (r - l + 1);
    long long coprime_pairs_num = count_coprime_pairs(l, r);
    long long divisor_pairs_num = 0;
    for (int g = l + (l == 1); g <= r; ++g) {
        divisor_pairs_num += 2 * (r / g - 1) + 1;
    }
    long long ans = whole - (coprime_pairs_num + divisor_pairs_num);
    std::cout << ans << std::endl;
    return 0;
}