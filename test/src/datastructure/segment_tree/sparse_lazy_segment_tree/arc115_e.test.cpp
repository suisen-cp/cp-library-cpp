#define PROBLEM "https://atcoder.jp/contests/arc115/tasks/arc115_e"

#include <algorithm>
#include <iostream>
#include <atcoder/modint>
#include "library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp"

using suisen::SparseLazySegmentTree;
using mint = atcoder::modint998244353;
using F = std::pair<mint, mint>;

mint op(mint x, mint y) {
    return x + y;
}
mint e() {
    return 0;
}
mint mapping(F f, mint x, int l, int r) {
    return f.first * x + f.second * (r - l);
}
F composition(F f, F g) {
    return { f.first * g.first, f.first * g.second + f.second };
}
F id() {
    return { 1, 0 };
}
mint init(int, int) {
    return 0;
}

using SegmentTree = SparseLazySegmentTree<int, mint, op, e, F, mapping, composition, id, init>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int &e : a) std::cin >> e;
    const int m = *std::max_element(a.begin(), a.end());
    SegmentTree seg(m);
    SegmentTree::reserve(10000000);
    mint sum = 1;
    for (int v : a) {
        seg.apply_all({ -1, sum });
        seg.apply(v, m, { 0, 0 });
        sum = seg.prod_all();
    }
    std::cout << seg.prod_all().val() << '\n';
    return 0;
}