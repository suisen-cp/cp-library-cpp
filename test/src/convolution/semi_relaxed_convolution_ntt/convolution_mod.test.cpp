#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <iostream>

#include <atcoder/modint>
#include <atcoder/convolution>

using mint = atcoder::modint998244353;

std::istream& operator>>(std::istream& in, mint& a) {
    long long e; in >> e; a = e;
    return in;
}

std::ostream& operator<<(std::ostream& out, const mint& a) {
    out << a.val();
    return out;
}

#include "library/convolution/semi_relaxed_convolution_ntt.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m;
    std::cin >> n >> m;

    std::vector<mint> a(n), b(m);
    for (auto& e : a) std::cin >> e;
    for (auto& e : b) std::cin >> e;

    suisen::SemiRelaxedConvolutionNTT<mint> conv(a);

    for (std::size_t i = 0; i < n + m - 1; ++i) {
        conv.append(i < b.size() ? b[i] : 0);
    }
    auto c = conv.get();
    for (std::size_t i = 0; i < n + m - 1; ++i) {
        std::cout << c[i] << " \n"[i == n + m - 2];
    }
    return 0;
}