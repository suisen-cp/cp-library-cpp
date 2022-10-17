#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial"

#include <iostream>
#include <atcoder/modint>

#include "library/math/sum_i^d_r^i.hpp"

int main() {
    using mint = atcoder::modint998244353;
    int r, d;
    long long n;
    std::cin >> r >> d >> n;
    std::cout << suisen::sum_i_i_pow_d_r_pow_i<mint>(d, r).sum(n).val() << std::endl;
    return 0;
}