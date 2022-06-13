#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include <iostream>
#include <tuple>

#include "library/datastructure/fenwick_tree/fenwick_tree_2d_sparse.hpp"
using suisen::FenwickTree2DSparse;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    FenwickTree2DSparse<long long> seg(n);
    std::vector<std::tuple<int, int, int>> points(n);
    for (int i = 0; i < n; ++i) {
        int x, y, w;
        std::cin >> x >> y >> w;
        points[i] = { x, y, w };
        seg.add_point(x, y);
    }
    seg.build();
    for (auto [x, y, w] : points) {
        seg.add(x, y, w);
    }
    for (int i = 0; i < q; ++i) {
        int l, d, r, u;
        std::cin >> l >> d >> r >> u;
        std::cout << seg.sum(l, r, d, u) << '\n';
    }
    return 0;
}