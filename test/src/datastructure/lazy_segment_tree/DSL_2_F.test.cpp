#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F"

#include <iostream>

#include "library/datastructure/lazy_segment_tree.hpp"
using suisen::LazySegmentTree;

constexpr int min_e = std::numeric_limits<int>::max();
int min_op(int x, int y) {
    return x < y ? x : y;
}
constexpr int update_e = -1;
int update_op(int f, int g) {
    return f == update_e ? g : f;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    LazySegmentTree seg(n, min_e, min_op, -1, update_op, update_op);
    for (int i = 0; i < q; ++i) {
        int t, l, r;
        std::cin >> t >> l >> r;
        ++r;
        if (t == 0) {
            int x;
            std::cin >> x;
            seg.apply(l, r, x);
        } else {
            std::cout << seg(l, r) << '\n';
        }
    }
    return 0;
}