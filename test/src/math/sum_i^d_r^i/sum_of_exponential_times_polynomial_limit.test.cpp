#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit"

#include <iostream>
#include <atcoder/modint>

#include "library/math/sum_i^d_r^i.hpp"

int main() {
    using mint = atcoder::modint998244353;
    int r, d;
    std::cin >> r >> d;
    std::cout << suisen::sum_i_i_pow_d_r_pow_i<mint>(d, r).sum().val() << std::endl;
    return 0;
}