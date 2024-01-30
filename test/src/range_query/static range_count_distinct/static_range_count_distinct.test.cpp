#define PROBLEM "https://judge.yosupo.jp/problem/static_range_count_distinct"

#include "library/range_query/static range_count_distinct.hpp"

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> a(n);
    for (int &e : a) std::cin >> e;

    suisen::StaticRangeCountDistinctOffline processor(a);
    processor.reserve(q);

    while (q--) {
        int l, r;
        std::cin >> l >> r;
        processor.add_query(l, r);
    }
    for (int ans : processor.solve()) {
        std::cout << ans << '\n';
    }
}