#define PROBLEM "https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/datastructure/fenwick_tree/rectangle_add_rectangle_sum.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    suisen::RectangleAddRectangleSum<mint> rectangle_add_rectangle_sum(2 * n);
    
    std::vector<std::tuple<int, int, int, int, mint>> add_queries(n);
    for (int i = 0; i < n; ++i) {
        int l, d, r, u, w;
        std::cin >> l >> d >> r >> u >> w;
        add_queries[i] = { l, d, r, u, w };
        rectangle_add_rectangle_sum.register_add_query_rectangle(l, r, d, u);
    }
    rectangle_add_rectangle_sum.build();
    for (const auto &[l, d, r, u, w] : add_queries) {
        rectangle_add_rectangle_sum.add(l, r, d, u, w);
    }
    for (int i = 0; i < q; ++i) {
        int l, d, r, u;
        std::cin >> l >> d >> r >> u;
        std::cout << rectangle_add_rectangle_sum.sum(l, r, d, u).val() << '\n';
    }
    return 0;
}