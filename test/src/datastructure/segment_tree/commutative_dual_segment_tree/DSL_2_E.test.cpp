#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E"

#include <iostream>

#include "library/datastructure/segment_tree/commutative_dual_segment_tree.hpp"
using suisen::CommutativeDualSegmentTree;

int mapping(int f, int x) { return f + x; }
int composition(int f, int g) { return f + g; }
int id() { return 0; }

int main() {
    int n, q;
    std::cin >> n >> q;
    CommutativeDualSegmentTree<int, int, mapping, composition, id> seg(n, 0);
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