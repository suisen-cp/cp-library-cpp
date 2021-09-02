#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

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
    std::vector<std::pair<long long, long long>> init(n);
    std::vector<std::tuple<int, long long, long long>> queries(q);
    for (int i = 0; i < n; ++i) {
        long long a, b;
        std::cin >> a >> b;
        init[i] = { a, b };
    }
    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        long long a, b = 0;
        if (t == 0) {
            std::cin >> a >> b;
        } else {
            std::cin >> a;
        }
        queries[i] = { t, a, b };
        if (t == 1) {
            pos.push_back(a);
        }
    }
    LiChaoSegmentTree<long long> seg(pos);
    for (const auto &[a, b] : init) {
        seg.add_line(a, b);
    }
    for (const auto &[t, a, b] : queries) {
        if (t == 0) {
            seg.add_line(a, b);
        } else {
            std::cout << *(seg(a)) << '\n';
        }
    }
    return 0;
}