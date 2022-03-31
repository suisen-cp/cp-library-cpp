#define PROBLEM "https://judge.yosupo.jp/problem/convex_layers"

#include <cassert>
#include <iostream>
#include <map>

#include "library/algorithm/dynamic_convex_hull_offline.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    
    std::vector<int> xs(n);
    std::vector<std::pair<int, int>> points(n);
    std::map<std::pair<int, int>, int> id;

    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        points[i] = { x, y };
        xs[i] = x;
        id[points[i]] = i;
    }

    suisen::DynamicConvexHullOffline hull(xs);
    for (const auto &[x, y] : points) hull.insert(x, y);

    std::vector<int> ans(n);
    int erased = 0;
    for (int i = 1; erased < n; ++i) {
        auto h = hull.get_hull();
        std::sort(h.begin(), h.end());
        assert(std::adjacent_find(h.begin(), h.end(), [&](auto &p, auto &q) { return p == q; }) == h.end());
        for (auto &[x, y] : h) {
            auto it = id.find({ x, y });
            assert(it != id.end());
            ans[it->second] = i;
            ++erased;
            hull.erase(x, y);
            id.erase(it);
        }
    }

    for (const auto &t : ans) {
        assert(t > 0);
        std::cout << t << '\n';
    }

    return 0;
}