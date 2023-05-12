#define PROBLEM "https://atcoder.jp/contests/abc237/tasks/abc237_g"

#include <iostream>
#include <variant>

#include "library/datastructure/segment_tree/sortable_segment_tree.hpp"

using S = std::monostate;
S op(S, S) { return {}; }
S e() { return {}; }
S toggle(S) { return {}; }

using SortableSegmentTree = suisen::SortableSegmentTree<S, op, e, toggle>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q, x;
    std::cin >> n >> q >> x;

    std::vector<std::pair<int, S>> init(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> init[i].first;
    }
    SortableSegmentTree seg(init);

    while (q --> 0) {
        int c, l, r;
        std::cin >> c >> l >> r;
        --l;
        if (c == 1) {
            seg.sort_asc(l, r);
        } else {
            seg.sort_dsc(l, r);
        }
    }
    int pos = 1;
    seg.foreach([&](int key, S) {
        if (key == x) std::cout << pos << '\n';
        ++pos;
    });
}