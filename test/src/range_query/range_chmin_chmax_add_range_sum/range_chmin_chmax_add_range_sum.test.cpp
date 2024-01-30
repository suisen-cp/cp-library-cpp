#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"

#include <iostream>

#include "library/range_query/range_chmin_chmax_add_range_sum.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<long long> a(n);
    for (auto &e : a) std::cin >> e;

    suisen::RangeChMinMaxAddRangeSum<long long> seg(n);
    for (int i = 0; i < n; ++i) {
        seg.update(i, i + 1, a[i]);
    }

    while (q --> 0) {
        int qt, l, r;
        std::cin >> qt >> l >> r;
        if (qt < 3) {
            long long b;
            std::cin >> b;
            if (qt == 0) seg.chmin(l, r, b);
            if (qt == 1) seg.chmax(l, r, b);
            if (qt == 2) seg.add(l, r, b);
        } else {
            std::cout << seg.sum(l, r) << '\n';
        }
    }
    return 0;
}