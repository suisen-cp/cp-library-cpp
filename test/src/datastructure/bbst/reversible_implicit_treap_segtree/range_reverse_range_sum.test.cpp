#define PROBLEM "https://judge.yosupo.jp/problem/range_reverse_range_sum"

#include <iostream>

#include "library/datastructure/bbst/reversible_implicit_treap_segtree.hpp"

long long op(long long x, long long y) {
    return x + y;
}
long long e() {
    return 0;
}
long long toggle(long long x) {
    return x;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    
    std::vector<long long> a(n);
    for (auto &e : a) std::cin >> e;

    suisen::ReversibleDynamicSegmentTree<long long, op, e, toggle> seg(a);
    for (int query_id = 0; query_id < q; ++query_id) {
        int t, l, r;
        std::cin >> t >> l >> r;
        if (t == 0) {
            seg.reverse(l, r);
        } else {
            std::cout << seg.prod(l, r) << '\n';
        }
    }
    return 0;
}