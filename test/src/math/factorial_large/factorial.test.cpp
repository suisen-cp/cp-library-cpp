#define PROBLEM "https://judge.yosupo.jp/problem/factorial"

#include <iostream>

#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/math/factorial_large.hpp"

int main() {
    suisen::factorial_large<mint> fac;

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        std::cout << fac.fac(n).val() << '\n';
    }
}