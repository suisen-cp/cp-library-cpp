#define PROBLEM "https://judge.yosupo.jp/problem/vertex_ad"

#include <iostream>
#include <atcoder/segtree>

#include "library/tree/heavy_light_decomposition.hpp"
using suisen::HeavyLightDecomposition;

constexpr long long op(long long x, long long y) { return x + y; }
constexpr long long e() { return 0LL; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<long long> a(n);
    for (long long &e : a) std::cin >> e;
    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    HeavyLightDecomposition hld(g);
    atcoder::segtree<long long, op, e> seg(n);
    for (int i = 0; i < n; ++i) {
        hld.update_point(i, [&](int v) { seg.set(v, a[i]); });
    }
    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int p, x;
            std::cin >> p >> x;
            hld.update_point(p, [&](int i) { seg.set(i, seg.get(i) + x); });
        } else {
            int u, v;
            std::cin >> u >> v;
            std::cout << hld.fold_path(u, v, 0LL, op, [&](int l, int r) { return seg.prod(l, r); }) << '\n';
        }
    }
    return 0;
}