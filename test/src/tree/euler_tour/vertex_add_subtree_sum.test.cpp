#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include <iostream>
#include <atcoder/segtree>

#include "library/tree/euler_tour.hpp"

using suisen::EulerTour;

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
    EulerTour et(g);
    atcoder::segtree<long long, op, e> seg(2 * n);
    for (int i = 0; i < n; ++i) {
        seg.set(et.visit_time(i), a[i]);
    }
    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int u, x;
            std::cin >> u >> x;
            int vis = et.visit_time(u);
            seg.set(vis, seg.get(vis) + x);
        } else {
            int u;
            std::cin >> u;
            std::cout << seg.prod(et.visit_time(u), et.leave_time(u)) << '\n';
        }
        std::cout.flush();
    }
    return 0;
}