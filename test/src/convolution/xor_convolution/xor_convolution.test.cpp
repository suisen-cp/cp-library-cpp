#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_xor_convolution"

#include <iostream>
#include <atcoder/modint>

#include "library/convolution/xor_convolution.hpp"

using mint = atcoder::modint998244353;

std::istream& operator>>(std::istream& in, mint &a) {
    long long e; in >> e; a = e;
    return in;
}

std::ostream& operator<<(std::ostream& out, const mint &a) {
    out << a.val();
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T> &a) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        out << a[i];
        if (i != n - 1) out << ' ';
    }
    return out;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<mint> a(1 << n), b(1 << n);
    for (auto &v : a) std::cin >> v;
    for (auto &v : b) std::cin >> v;
    std::cout << suisen::xor_convolution<mint>(std::move(a), std::move(b)) << std::endl;
    return 0;
}