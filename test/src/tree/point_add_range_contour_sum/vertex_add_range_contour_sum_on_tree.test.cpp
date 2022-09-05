#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree"

#include <iostream>

#include "library/tree/point_add_range_contour_sum.hpp"

long long op(long long x, long long y) {
    return x + y;
}
long long e() {
    return 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;

    std::vector<long long> a(n);
    for (auto &e : a) std::cin >> e;

    suisen::PointAddRangeContourSum<long long, op, e> g(a);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }
    g.build();

    while (q --> 0) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 0) {
            int p, x;
            std::cin >> p >> x;
            g.add(p, x);
        } else {
            int p, l, r;
            std::cin >> p >> l >> r;
            std::cout << g.sum(p, l, r) << '\n';
        }
    }

    return 0;
}