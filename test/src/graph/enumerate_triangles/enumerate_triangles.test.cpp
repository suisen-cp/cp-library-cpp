#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_triangles"

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

#include "library/graph/enumerate_triangles.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<mint> x(n);
    for (auto &e : x) std::cin >> e;

    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    mint ans = 0;
    suisen::enumerate_triangles(g, [&](int i, int j, int k) { ans += x[i] * x[j] * x[k]; });
    std::cout << ans << std::endl;

    return 0;
}