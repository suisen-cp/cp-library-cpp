#define PROBLEM "https://judge.yosupo.jp/problem/gcd_convolution"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

std::istream& operator>>(std::istream& in, mint &a) {
    long long e; in >> e; a = e;
    return in;
}

std::ostream& operator<<(std::ostream& out, const mint &a) {
    out << a.val();
    return out;
}

#include "library/convolution/gcd_convolution.hpp"


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<mint> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i <= n; ++i) std::cin >> b[i];

    std::vector<mint> c = suisen::gcd_convolution(a, b);
    for (int i = 1; i <= n; ++i) std::cout << c[i] << " \n"[i == n];

    return 0;
}