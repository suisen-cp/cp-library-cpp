#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include <iostream>
#include <tuple>

#include "library/datastructure/segment_tree_2d.hpp"
using suisen::SegmentTree2D;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    SegmentTree2D seg(n, 0LL, std::plus<long long>());
    std::vector<std::tuple<int, int, int>> points(n);
    for (int i = 0; i < n; ++i) {
        int x, y, w;
        std::cin >> x >> y >> w;
        points[i] = { x, y, w };
        seg.insert(x, y);
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