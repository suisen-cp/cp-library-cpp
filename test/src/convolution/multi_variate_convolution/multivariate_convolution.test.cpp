#define PROBLEM "https://judge.yosupo.jp/problem/multivariate_convolution"

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

#include "library/convolution/multi_variate_convolution.hpp"
using namespace suisen;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int k;
    std::cin >> k;
    std::vector<int> dim(k);
    for (int &e : dim) std::cin >> e;

    multi_variate_convolution convolution(dim);
    int n = convolution.size();

    std::vector<mint> f(n), g(n);
    for (auto &e : f) std::cin >> e;
    for (auto &e : g) std::cin >> e;

    auto h = convolution(f, g);

    for (int i = 0; i < n; ++i) std::cout << h[i] << " \n"[i == n - 1];

    return 0;
}