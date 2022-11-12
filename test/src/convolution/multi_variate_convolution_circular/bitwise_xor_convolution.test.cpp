#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_xor_convolution"

#include <iostream>

#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/convolution/multi_variate_convolution_circular.hpp"

int main() {
    using suisen::multi_variate_convolution_circular;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<mint> a(1 << n), b(1 << n);

    for (int i = 0, v; i < 1 << n; ++i) std::cin >> v, a[i] = v;
    for (int i = 0, v; i < 1 << n; ++i) std::cin >> v, b[i] = v;

    multi_variate_convolution_circular<mint> conv(std::vector<int>(n, 2));

    std::vector<mint> c = conv(a, b);
    for (int i = 0; i < 1 << n; ++i) std::cout << c[i].val() << " \n"[i == (1 << n) - 1];

    return 0;
}