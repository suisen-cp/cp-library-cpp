#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D"

#include <iostream>

#include "library/datastructure/segment_tree/dual_segment_tree.hpp"
using suisen::DualSegmentTree;

int mapping(int f, int x) {
    return f < 0 ? x : f;
}
int composition(int f, int g) {
    return f < 0 ? g : f;
}
int id() {
    return -1;
}

int main() {
    int n, q;
    std::cin >> n >> q;
    DualSegmentTree<int, int, mapping, composition, id> seg(n, std::numeric_limits<int>::max());
    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int s, t, x;
            std::cin >> s >> t >> x;
            seg.apply(s, ++t, x);
        } else {
            int i;
            std::cin >> i;
            std::cout << seg[i] << '\n';
        }
    }
    return 0;
}