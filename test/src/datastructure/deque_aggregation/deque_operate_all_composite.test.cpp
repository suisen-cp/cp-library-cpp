#define PROBLEM "https://judge.yosupo.jp/problem/deque_operate_all_composite"

#include <iostream>

#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/algebra/monoid/affine.hpp"
#include "library/datastructure/deque_aggregation.hpp"

using suisen::Affine;
using suisen::DequeAggregation;

Affine<mint> op(Affine<mint> f, Affine<mint> g) { return g.compose(f); }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    DequeAggregation<Affine<mint>, op, Affine<mint>::id> dq;

    int q;
    std::cin >> q;

    for (int i = 0; i < q; ++i) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 0) {
            int a, b;
            std::cin >> a >> b;
            dq.push_front({ a, b });
        } else if (query_type == 1) {
            int a, b;
            std::cin >> a >> b;
            dq.push_back({ a, b });
        } else if (query_type == 2) {
            dq.pop_front();
        } else if (query_type == 3) {
            dq.pop_back();
        } else {
            int x;
            std::cin >> x;
            std::cout << dq.prod().affine(x).val() << '\n';
        }
    }
    
    return 0;
}