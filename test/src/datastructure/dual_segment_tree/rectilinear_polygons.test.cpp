#define PROBLEM "https://atcoder.jp/contests/abc211/tasks/abc211_f"

#include <algorithm>
#include <iostream>
#include <tuple>

#include "library/datastructure/dual_segment_tree.hpp"
using suisen::DualSegmentTree;

constexpr int M = 100010;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::vector<std::tuple<int, int, int>>> event(M);
    DualSegmentTree seg1(M, 0, 0, std::plus<int>(), std::plus<int>());
    for (int i = 0; i < n; ++i) {
        int m;
        std::cin >> m;
        std::vector<std::pair<int, int>> polygon(m);
        for (int j = 0; j < m; ++j) {
            int x, y;
            std::cin >> x >> y;
            polygon[j] = {x, y};
        }
        std::vector<std::tuple<int, int, int>> t;
        for (int j = 0; j < m; j += 2) {
            auto [x, y1] = polygon[j];
            auto [_, y2] = polygon[j + 1];
            t.emplace_back(x, std::min(y1, y2), std::max(y1, y2));
        }
        std::sort(t.begin(), t.end());
        for (auto [x, yl, yr] : t) {
            int sgn = seg1[yl] & 1 ? -1 : 1;
            event[x].emplace_back(yl, yr, sgn);
            seg1.apply(yl, yr, 1);
        }
        for (auto [_, yl, yr] : t) {
            seg1.apply(yl, yr, -1);
        }
    }
    int q;
    std::cin >> q;
    std::vector<std::tuple<int, int, int>> qs(q);
    for (int i = 0; i < q; ++i) {
        int x, y;
        std::cin >> x >> y;
        qs[i] = {x, y, i};
    }
    std::sort(qs.begin(), qs.end());
    std::vector<int> ans(q);
    DualSegmentTree seg(M, 0, 0, std::plus<int>(), std::plus<int>());
    int prev = 0;
    for (auto [x, y, id] : qs) {
        for (; prev <= x; ++prev) {
            for (auto [yl, yr, sgn] : event[prev]) seg.apply(yl, yr, sgn);
        }
        ans[id] = seg[y];
    }
    for (auto v : ans) {
        std::cout << v << '\n';
    }
    return 0;
}