#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <functional>
#include <iostream>

#include "library/datastructure/segment_tree.hpp"

using suisen::SegmentTree;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<long long> a(n);
    for (auto &e : a) std::cin >> e;
    SegmentTree seg(std::move(a), 0LL, std::plus<long long>());
    while (q --> 0) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int p, x;
            std::cin >> p >> x;
            seg[p] += x;
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << seg(l, r) << '\n';
        }
    }
    return 0;
}