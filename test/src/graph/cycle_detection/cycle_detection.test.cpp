#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"

#include <algorithm>
#include <iostream>

#include "library/graph/cycle_detection.hpp"
using namespace suisen;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    DirectedGraphBuilder<int> gb(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        gb.emplace_edge(u, v, i);
    }
    Graph<int> g = gb.build();

    const auto optional_cycle = get_cycle_directed(g);
    if (optional_cycle.has_value()) {
        const auto &cycle = *optional_cycle;
        const int sz = cycle.size();
        std::cout << sz << '\n';
        for (int i = 0; i < sz; ++i) {
            std::cout << g.get_weight(cycle[i]) << '\n';
        }
    } else {
        std::cout << -1 << '\n';
    }
    return 0;
}