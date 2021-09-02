#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"

#include <iostream>
#include <tuple>

#include "library/datastructure/li_chao_segment_tree.hpp"

using suisen::LiChaoSegmentTree;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<long long> pos;
    std::vector<std::tuple<long long, long long, long long, long long>> init(n);
    std::vector<std::tuple<int, long long, long long, long long, long long>> queries(q);
    for (int i = 0; i < n; ++i) {
        long long l, r, a, b;
        std::cin >> l >> r >> a >> b;
        init[i] = { l, r, a, b };
    }
    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        long long l = 0, r = 0, a = 0, b = 0;
        if (t == 0) {
            std::cin >> l >> r >> a >> b;
        } else {
            std::cin >> l;
        }
        queries[i] = { t, l, r, a, b };
        if (t == 1) {
            pos.push_back(l);
        }
    }
    LiChaoSegmentTree<long long> seg(pos);
    for (const auto &[l, r, a, b] : init) {
        seg.add_segment(l, r - 1, a, b);
    }
    for (const auto &[t, l, r, a, b] : queries) {
        if (t == 0) {
            seg.add_segment(l, r - 1, a, b);
        } else {
            auto res = seg(l);
            if (res.has_value()) {
                std::cout << *res << '\n';
            } else {
                std::cout << "INFINITY" << '\n';
            }
        }
    }
    return 0;
}