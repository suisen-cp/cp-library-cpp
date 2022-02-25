#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_totient_function"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/number/sum_of_totient_function.hpp"

int main() {
    uint64_t n;
    std::cin >> n;
    suisen::SumOfTotientFunction<mint> sum(n);
    std::cout << sum().val() << std::endl;
    return 0;
}