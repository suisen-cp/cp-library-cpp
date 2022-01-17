#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include <iostream>
#include <tuple>

#include "library/datastructure/segment_tree/segment_tree_2d_sparse.hpp"
using suisen::SegmentTree2DSparse;

long long op(long long x, long long y) {
    return x + y;
}
long long e() {
    return 0LL;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    SegmentTree2DSparse<long long, op, e> seg(n);
    std::vector<std::tuple<int, int, int>> points(n);
    for (int i = 0; i < n; ++i) {
        int x, y, w;
        std::cin >> x >> y >> w;
        points[i] = { x, y, w };
        seg.add_point(x, y);
    }
    seg.build();
    for (auto [x, y, w] : points) {
        seg[{x, y}] += w;
    }
    for (int i = 0; i < q; ++i) {
        int l, d, r, u;
        std::cin >> l >> d >> r >> u;
        std::cout << seg(l, r, d, u) << '\n';
    }
    return 0;
}