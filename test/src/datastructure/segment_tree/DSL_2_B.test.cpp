#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"

#include <iostream>

#include "library/datastructure/segment_tree.hpp"
using suisen::SegmentTree;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    SegmentTree seg(n, 0, std::plus<int>());
    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int i, x;
            std::cin >> i >> x;
            seg[i - 1] += x;
        } else {
            int s, t;
            std::cin >> s >> t;
            std::cout << seg(--s, t) << '\n';
        }
    }
    return 0;
}