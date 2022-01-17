#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F"

#include <iostream>

#include "library/datastructure/segment_tree/lazy_segment_tree.hpp"
using suisen::LazySegmentTree;

int op(int x, int y) {
    return x < y ? x : y;
}
int e() {
    return std::numeric_limits<int>::max();
}
int mapping(int f, int g) {
    return f < 0 ? g : f;
}
int composition(int f, int g) {
    return f < 0 ? g : f;
}
int id() {
    return -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    LazySegmentTree<int, op, e, int, mapping, composition, id> seg(n);
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