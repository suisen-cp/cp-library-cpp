#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include <iostream>
#include <tuple>

#include "library/datastructure/fenwick_tree/fenwick_tree_2d_sparse.hpp"
using suisen::FenwickTree2DSparse;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    FenwickTree2DSparse<long long> seg(n + q);

    std::vector<std::tuple<int, int, int>> init(n);
    for (int i = 0; i < n; ++i) {
        int x, y, w;
        std::cin >> x >> y >> w;
        init[i] = { x, y, w };
        seg.add_point(x, y);
    }
    std::vector<std::tuple<int, int, int, int, int>> queries(q);
    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int x, y, w;
            std::cin >> x >> y >> w;
            queries[i] = { t, x, y, w, 0 };
            seg.add_point(x, y);
        } else {
            int l, d, r, u;
            std::cin >> l >> d >> r >> u;
            queries[i] = { t, l, r, d, u };
        }
    }

    seg.build();

    for (auto [x, y, w] : init) {
        seg.add(x, y, w);
    }

    for (const auto &q : queries) {
        if (std::get<0>(q) == 0) {
            auto [t, x, y, w, _] = q;
            seg.add(x, y, w);
        } else {
            auto [t, l, r, d, u] = q;
            std::cout << seg.sum(l, r, d, u) << '\n';
        }
    }

    return 0;
}