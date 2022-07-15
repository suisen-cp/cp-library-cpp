#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_point_get"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/datastructure/segment_tree/dual_segment_tree.hpp"

mint mapping(std::pair<mint, mint> f, mint x) {
    return f.first * x + f.second;
}
std::pair<mint, mint> composition(std::pair<mint, mint> f, std::pair<mint, mint> g) {
    return { f.first * g.first, f.first * g.second + f.second };
}
std::pair<mint, mint> id() {
    return { 1, 0 };
}
using Segtree = suisen::DualSegmentTree<mint, std::pair<mint, mint>, mapping, composition, id>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<mint> a(n);
    for (auto &e : a) {
        int v;
        std::cin >> v;
        e = v;
    }

    Segtree seg(a);
    while (q --> 0) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 0) {
            int l, r, b, c;
            std::cin >> l >> r >> b >> c;
            seg.apply(l, r, { b, c });
        } else {
            int x;
            std::cin >> x;
            std::cout << seg.get(x).val() << '\n';
        }
    }

    return 0;
}