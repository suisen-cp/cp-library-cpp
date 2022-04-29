#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include <iostream>
#include "library/convolution/arbitrary_mod_convolution.hpp"

using mint = atcoder::modint1000000007;

std::istream& operator>>(std::istream& in, mint &a) {
    long long e; in >> e; a = e;
    return in;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m;
    std::cin >> n >> m;

    std::vector<mint> a(n), b(m);
    for (auto &e : a) std::cin >> e;
    for (auto &e : b) std::cin >> e;

    std::vector<mint> c = suisen::arbitrary_mod_convolution(a, b);
    for (std::size_t i = 0; i < n + m - 1; ++i) {
        std::cout << c[i].val() << " \n"[i == n + m - 2];
    }
    return 0;
}