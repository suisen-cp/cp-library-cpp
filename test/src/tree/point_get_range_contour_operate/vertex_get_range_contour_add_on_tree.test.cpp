#define PROBLEM "https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree"

#include <iostream>

#include "library/tree/point_get_range_contour_operate.hpp"

using T = long long;
using F = long long;
T mapping(F f, T x) {
    return f + x;
}
F composition(F f, F g) {
    return f + g;
}
F id() {
    return 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    using suisen::PointGetRangeContourOperate;

    int n, q;
    std::cin >> n >> q;

    std::vector<T> a(n);
    for (auto &e : a) std::cin >> e;

    PointGetRangeContourOperate<T, F, mapping, composition, id> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }
    g.build(a);

    while (q --> 0) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 0) {
            int p, l, r, x;
            std::cin >> p >> l >> r >> x;
            g.apply(p, l, r, x);
        } else {
            int p;
            std::cin >> p;
            std::cout << g.get(p) << '\n';
        }
    }
}