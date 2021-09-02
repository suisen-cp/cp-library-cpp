#define PROBLEM "https://atcoder.jp/contests/arc115/tasks/arc115_e"

#include <algorithm>
#include <iostream>
#include <atcoder/modint>
#include "library/datastructure/sparse_lazy_segment_tree.hpp"

using suisen::SparseLazySegmentTree;
using mint = atcoder::modint998244353;
using S = std::pair<mint, int>;
using F = std::pair<mint, mint>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int &e : a) std::cin >> e;
    const int m = *std::max_element(a.begin(), a.end());
    SparseLazySegmentTree seg(
        m,
        S { 0, 0 },
        [](const S &x, const S &y) -> S { return { x.first + y.first, x.second + y.second }; },
        F { 1, 0 },
        [](const F &f, const S &x) -> S { return { f.first * x.first + f.second * x.second, x.second }; },
        [](const F &f, const F &g) -> F { return { f.first * g.first, f.first * g.second + f.second }; },
        [](int l, int r) -> S { return { 0, r - l }; }
    );
    mint sum = 1;
    for (int v : a) {
        seg.apply_all({ -1, sum });
        seg.apply(v, m, { 0, 0 });
        sum = seg.prod_all().first;
    }
    std::cout << seg.prod_all().first.val() << '\n';
    return 0;
}