#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_sort_range_composite"

#include <iostream>

#include "library/datastructure/segment_tree/sortable_segment_tree.hpp"

#include <atcoder/modint>

using mint = atcoder::modint998244353;

using S = std::tuple<mint, mint, mint>;
S make(mint a, mint b) {
    return { a, b, b };
}
S op(S x, S y) {
    const auto& [xa, xb, rxb] = x;
    const auto& [ya, yb, ryb] = y;
    return { xa * ya, ya * xb + yb, xa * ryb + rxb };
}
S e() {
    return { 1, 0, 0 };
}
S toggle(S x) {
    const auto& [xa, xb, rxb] = x;
    return { xa, rxb, xb };
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    using SortableSegmentTree = suisen::SortableSegmentTree<S, op, e, toggle>;
    using size_type = SortableSegmentTree::size_type;
    using key_type = SortableSegmentTree::key_type;

    int n, q;
    std::cin >> n >> q;

    std::vector<std::pair<key_type, S>> init(n);
    for (int i = 0; i < n; ++i) {
        key_type p;
        int a, b;
        std::cin >> p >> a >> b;
        init[i] = { p, make(a, b) };
    }

    SortableSegmentTree seg(init);
    while (q --> 0) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 0) {
            size_type i;
            key_type p;
            int a, b;
            std::cin >> i >> p >> a >> b;
            seg.set_key_value(i, p, make(a, b));
        } else if (query_type == 1) {
            size_type l, r;
            int x;
            std::cin >> l >> r >> x;
            auto [a, b, _] = seg.prod(l, r);
            std::cout << (a * x + b).val() << '\n';
        } else if (query_type == 2) {
            size_type l, r;
            std::cin >> l >> r;
            seg.sort_asc(l, r);
        } else {
            size_type l, r;
            std::cin >> l >> r;
            seg.sort_dsc(l, r);
        }
    }
}