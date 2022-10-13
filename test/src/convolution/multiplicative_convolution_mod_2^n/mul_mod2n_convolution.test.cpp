#define PROBLEM "https://judge.yosupo.jp/problem/mul_mod2n_convolution"

#include <iostream>
#include <atcoder/modint>

#include "library/convolution/multiplicative_convolution_mod_2^n.hpp"

int main() {
    using mint = atcoder::modint998244353;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<mint> a(1 << n), b(1 << n);
    for (int i = 0, v; i < 1 << n; ++i) std::cin >> v, a[i] = v;
    for (int i = 0, v; i < 1 << n; ++i) std::cin >> v, b[i] = v;

    std::vector<mint> c = suisen::multiplicative_convolution_mod_2_n(a, b);

    for (int i = 0; i < 1 << n; ++i) {
        std::cout << c[i].val();
        if (i + 1 != 1 << n) std::cout << ' ';
    }
    std::cout << '\n';
    return 0;
}