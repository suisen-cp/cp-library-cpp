#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E"

#include <iostream>

#include "library/datastructure/dual_segment_tree.hpp"
using suisen::DualSegmentTree;

int main() {
    int n, q;
    std::cin >> n >> q;
    DualSegmentTree seg(n, 0, 0, std::plus<int>(), std::plus<int>());
    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int s, t, x;
            std::cin >> s >> t >> x;
            seg.apply(--s, t, x);
        } else {
            int i;
            std::cin >> i;
            std::cout << seg[--i] << '\n';
        }
    }
    return 0;
}