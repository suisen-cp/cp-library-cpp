#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include <iostream>
#include <atcoder/segtree>

#include "library/tree/heavy_light_decomposition.hpp"
using suisen::HeavyLightDecomposition;

constexpr long long op(long long x, long long y) { return x + y; }
constexpr long long e() { return  0LL; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<long long> a(n);
    for (long long &e : a) std::cin >> e;
    std::vector<std::vector<int>> g(n);
    for (int i = 1; i < n; ++i) {
        int p;
        std::cin >> p;
        g[i].push_back(p);
        g[p].push_back(i);
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
            int u, x;
            std::cin >> u >> x;
            hld.update_point(u, [&](int v) { seg.set(v, seg.get(v) + x); });
        } else {
            int u;
            std::cin >> u;
            std::cout << hld.fold_subtree<long long>(u, [&](int l, int r) { return seg.prod(l, r); }) << '\n';
        }
        std::cout.flush();
    }
    return 0;
}