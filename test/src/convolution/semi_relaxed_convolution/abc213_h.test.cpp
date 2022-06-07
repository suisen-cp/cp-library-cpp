#define PROBLEM "https://atcoder.jp/contests/abc213/tasks/abc213_h"

#include <iostream>
#include <tuple>

#include <atcoder/modint>
#include <atcoder/convolution>

using mint = atcoder::modint998244353;

std::istream& operator>>(std::istream& in, mint &a) {
    long long e; in >> e; a = e;
    return in;
}

std::ostream& operator<<(std::ostream& out, const mint &a) {
    out << a.val();
    return out;
}

#include "library/convolution/semi_relaxed_convolution.hpp"
using suisen::SemiRelaxedConvolution;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, t;
    std::cin >> n >> m >> t;

    std::vector<std::vector<std::pair<int, SemiRelaxedConvolution<mint>>>> p(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;

        std::vector<mint> l(t);
        for (auto &e : l) std::cin >> e;

        SemiRelaxedConvolution<mint> conv { l, [](const auto &a, const auto &b) { return atcoder::convolution(a, b); } };
        p[u].emplace_back(v, conv);
        p[v].emplace_back(u, conv);
    }

    std::vector<std::vector<mint>> f(n, std::vector<mint>(t + 1, 0));
    f[0][0] = 1;

    for (int i = 0; i < t; ++i) {
        for (int u = 0; u < n; ++u) for (auto &[v, conv] : p[u]) {
            f[u][i + 1] += conv.append(f[v][i]);
        }
    }

    std::cout << f[0][t].val() << std::endl;

    return 0;
}