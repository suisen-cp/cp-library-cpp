#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I"

#include <iostream>

#include "library/datastructure/segment_tree/lazy_segment_tree.hpp"
using suisen::LazySegmentTree;

using S = std::pair<long long, int>;
using F = long long;

S op(S p1, S p2) {
    auto [s1, l1] = p1;
    auto [s2, l2] = p2;
    return { s1 + s2, l1 + l2 };
}
S e() {
    return { 0LL, 0 };
}
S mapping(F f, S p) {
    int l = p.second;
    return f == std::numeric_limits<long long>::min() ? p : std::make_pair(f * l, l);
}
F composition(F f, F g) {
    return f == std::numeric_limits<long long>::min() ? g : f;
}
F id() {
    return std::numeric_limits<long long>::min();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    LazySegmentTree<S, op, e, F, mapping, composition, id> seg(std::vector<S>(n, { 0LL, 1 }));
    for (int i = 0; i < q; ++i) {
        int t, l, r;
        std::cin >> t >> l >> r;
        ++r;
        if (t == 0) {
            long long x;
            std::cin >> x;
            seg.apply(l, r, x);
        } else {
            std::cout << seg(l, r).first << '\n';
        }
    }
    return 0;
}