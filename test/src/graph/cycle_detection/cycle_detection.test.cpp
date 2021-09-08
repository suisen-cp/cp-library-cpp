#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"

#include <algorithm>
#include <iostream>

#include "library/graph/cycle_detection.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(n);
    std::vector<long long> edges(m);
    for (int i = 0; i < m; ++i) {
        long long u, v;
        std::cin >> u >> v;
        edges[i] = u << 40 | v << 20 | i;
        g[u].push_back(v);
    }
    std::sort(edges.begin(), edges.end());
    const auto optional_cycle = suisen::get_cycle_digraph(g);
    if (optional_cycle.has_value()) {
        const auto &cycle = *optional_cycle;
        const int sz = cycle.size();
        std::cout << sz << '\n';
        for (int i = 0; i < sz; ++i) {
            const long long u = cycle[i], v = cycle[(i + 1) % sz];
            std::cout << (*std::lower_bound(edges.begin(), edges.end(), u << 40 | v << 20) & ((1 << 20) - 1)) << '\n';
        }
    } else {
        std::cout << -1 << '\n';
    }
    return 0;
}