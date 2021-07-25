#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"

#include <iostream>

#include "library/datastructure/segment_tree.hpp"
using suisen::SegmentTree;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    SegmentTree seg(n, std::numeric_limits<int>::max(), [](int x, int y){ return std::min(x, y); });
    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int i, x;
            std::cin >> i >> x;
            seg[i] = x;
        } else {
            int s, t;
            std::cin >> s >> t;
            std::cout << seg(s, ++t) << '\n';
        }
    }
    return 0;
}