#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include <iostream>
#include <atcoder/segtree>

#include "library/tree/euler_tour.hpp"
using suisen::EulerTour;

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
    EulerTour et(g);
    atcoder::segtree<long long, op, e> seg(2 * n);
    for (int i = 0; i < n; ++i) {
        seg.set(et.visit_time(i), +a[i]);
        seg.set(et.leave_time(i), -a[i]);
    }
    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int p, x;
            std::cin >> p >> x;
            int l = et.visit_time(p), r = et.leave_time(p);
            seg.set(l, seg.get(l) + x);
            seg.set(r, seg.get(r) - x);
        } else {
            int u, v;
            std::cin >> u >> v;
            int a = et.lca(u, v);
            long long sum_au = seg.prod(et.visit_time(a), et.visit_time(u) + 1);
            long long sum_av = seg.prod(et.visit_time(a) + 1, et.visit_time(v) + 1);
            std::cout << sum_au + sum_av << '\n';
        }
    }
    return 0;
}