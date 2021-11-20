#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <iostream>

#include "library/datastructure/segment_tree_2d.hpp"
using suisen::SegmentTree2D;

long long op(long long x, long long y) {
    return x + y;
}
long long e() {
    return 0;
}

constexpr int L = 25;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<std::vector<long long>> a(L, std::vector<long long>(n));
    for (int i = 0; i < n; ++i) {
        long long v;
        std::cin >> v;
        for (int j = 0; j < L; ++j) a[j][i] = v & (3LL << (2 * j));
    }

    SegmentTree2D<long long, op, e> seg(a);
    while (q --> 0) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int p, x;
            std::cin >> p >> x;
            long long val = seg(0, L, p, p + 1) + x;
            for (int j = 0; j < L; ++j) {
                seg.set(j, p, val & (3LL << (2 * j)));
            }
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << seg(0, L, l, r) << '\n';
        }
    }
    return 0;
}