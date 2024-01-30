#define PROBLEM "https://yukicoder.me/problems/no/502"

#include <iostream>

#include <atcoder/modint>

using mint = atcoder::modint1000000007;

#include "library/math/factorial_large.hpp"

int main() {
    long long n;
    std::cin >> n;
    std::cout << suisen::factorial_large<mint>{}.fac(n).val() << '\n';
}