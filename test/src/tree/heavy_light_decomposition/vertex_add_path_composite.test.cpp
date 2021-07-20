#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"

#include <iostream>
#include <atcoder/segtree>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/tree/heavy_light_decomposition.hpp"
using suisen::HeavyLightDecomposition;

struct F {
    mint a, b;
    F(mint a, mint b) : a(a), b(b) {}
    F() : F(1, 0) {}
    mint apply(mint x) { return a * x + b; }
};

F op(F f, F g) { return F(g.a * f.a, g.a * f.b + g.b); }
F op_rev(F f, F g) { return F(f.a * g.a, f.a * g.b + f.b); }
F e() { return F{}; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<F> fs(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        fs[i] = F(a, b);
    }
    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    HeavyLightDecomposition hld(g);
    atcoder::segtree<F, op, e> seg(n);
    atcoder::segtree<F, op_rev, e> seg_rev(n);
    for (int i = 0; i < n; ++i) {
        hld.update_point(i, [&](int v) {
            seg.set(v, fs[i]);
            seg_rev.set(v, fs[i]);
        });
    }
    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int p, c, d;
            std::cin >> p >> c >> d;
            hld.update_point(p, [&](int v) {
                seg.set(v, F(c, d));
                seg_rev.set(v, F(c, d));
            });
        } else {
            int u, v, x;
            std::cin >> u >> v >> x;
            std::cout << hld.fold_path_noncommutative(
                u, v,
                F{}, op,
                [&](int l, int r) { return seg.prod(l, r); },
                [&](int l, int r) { return seg_rev.prod(l, r); }
            ).apply(x).val() << '\n';
        }
        std::cout.flush();
    }
    return 0;
}