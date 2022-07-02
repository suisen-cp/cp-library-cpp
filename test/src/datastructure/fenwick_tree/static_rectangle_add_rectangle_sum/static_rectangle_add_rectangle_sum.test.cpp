#define PROBLEM "https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    
    std::vector<suisen::AddQuery<mint>> add_queries(n);
    for (int i = 0; i < n; ++i) {
        int l, d, r, u, w;
        std::cin >> l >> d >> r >> u >> w;
        add_queries[i] = { l, r, d, u, w };
    }
    std::vector<suisen::SumQuery> sum_queries(q);
    for (int i = 0; i < q; ++i) {
        int l, d, r, u;
        std::cin >> l >> d >> r >> u;
        sum_queries[i] = { l, r, d, u };
    }
    for (mint ans : suisen::static_rectangle_add_rectangle_sum(add_queries, sum_queries)) {
        std::cout << ans.val() << '\n';
    }
    return 0;
}