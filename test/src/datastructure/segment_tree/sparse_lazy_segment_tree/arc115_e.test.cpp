#define PROBLEM "https://atcoder.jp/contests/arc115/tasks/arc115_e"

#include <algorithm>
#include <iostream>
#include <atcoder/modint>
#include "library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp"

using suisen::SparseLazySegmentTree;
using mint = atcoder::modint998244353;
using S = std::pair<mint, int>;
using F = std::pair<mint, mint>;

S op(S x, S y) {
    return { x.first + y.first, x.second + y.second };
}
S e() {
    return { 0, 0 };
}
S mapping(F f, S x) {
    return { f.first * x.first + f.second * x.second, x.second };
}
F composition(F f, F g) {
    return { f.first * g.first, f.first * g.second + f.second };
}
F id() {
    return { 1, 0 };
}
S init(int l, int r) {
    return { 0, r - l };
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int &e : a) std::cin >> e;
    const int m = *std::max_element(a.begin(), a.end());
    SparseLazySegmentTree<int, S, op, e, F, mapping, composition, id, init> seg(m);
    mint sum = 1;
    for (int v : a) {
        seg.apply_all({ -1, sum });
        seg.apply(v, m, { 0, 0 });
        sum = seg.prod_all().first;
    }
    std::cout << seg.prod_all().first.val() << '\n';
    return 0;
}