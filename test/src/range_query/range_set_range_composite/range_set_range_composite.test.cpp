#define PROBLEM "https://judge.yosupo.jp/problem/range_set_range_composite"

#include "library/range_query/range_set_range_composite.hpp"

#include <iostream>

#include <atcoder/modint>

using mint = atcoder::modint998244353;

using affine = std::pair<mint, mint>;

affine op(affine f, affine g) {
    return { g.first * f.first, g.first * f.second + g.second };
}
affine e() {
    return affine{ 1, 0 };
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<affine> init(n);
        for (int i = 0; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        init[i] = { a, b };
    }
    suisen::RangeSetRangeComposite<affine, op, e> seg(init);

    while (q--) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 0) {
            int l, r, c, d;
            std::cin >> l >> r >> c >> d;
            seg.set(l, r, affine{ c, d });
        } else {
            int l, r, x;
            std::cin >> l >> r >> x;
            auto [c, d] = seg.prod(l, r);
            std::cout << (c * x + d).val() << '\n';
        }
    }
}