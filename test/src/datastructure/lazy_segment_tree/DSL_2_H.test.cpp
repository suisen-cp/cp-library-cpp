#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H"

#include <iostream>

#include "library/datastructure/lazy_segment_tree.hpp"
using suisen::LazySegmentTree;

constexpr int min_e = std::numeric_limits<int>::max();
int min_op(int x, int y) {
    return x < y ? x : y;
}
constexpr long long id = 0;
constexpr std::plus<int> mapping, composition;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    LazySegmentTree seg(std::vector<int>(n, 0), min_e, min_op, id, mapping, composition);
    for (int i = 0; i < q; ++i) {
        int t, l, r;
        std::cin >> t >> l >> r;
        ++r;
        if (t == 0) {
            long long x;
            std::cin >> x;
            seg.apply(l, r, x);
        } else {
            std::cout << seg(l, r) << '\n';
        }
    }
    return 0;
}