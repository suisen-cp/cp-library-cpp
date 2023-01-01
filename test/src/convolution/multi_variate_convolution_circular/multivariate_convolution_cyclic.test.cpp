#define PROBLEM "https://judge.yosupo.jp/problem/multivariate_convolution_cyclic"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint;

std::istream& operator>>(std::istream& in, mint &a) {
    long long e; in >> e; a = e;
    return in;
}

std::ostream& operator<<(std::ostream& out, const mint &a) {
    out << a.val();
    return out;
}

#include "library/convolution/multi_variate_convolution_circular.hpp"

int main() {
    int p, k;
    std::cin >> p >> k;
    
    mint::set_mod(p);

    int n = 1;
    std::vector<int> ns(k);
    for (auto &e : ns) std::cin >> e, n *= e;

    suisen::multi_variate_convolution_circular<mint> conv(ns);

    std::vector<mint> f(n), g(n);
    for (auto &e : f) std::cin >> e;
    for (auto &e : g) std::cin >> e;
    std::vector<mint> h = conv(f, g);

    for (int i = 0; i < n; ++i) {
        std::cout << h[i].val() << " \n"[i + 1 == n];
    }
}