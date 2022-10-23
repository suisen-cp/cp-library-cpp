#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection_undirected"

#include <algorithm>
#include <iostream>

#include "library/graph/cycle_detection.hpp"
using namespace suisen;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    UndirectedGraphBuilder<int> gb(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        gb.emplace_edge(u, v, i);
    }
    Graph<int> g = gb.build();

    const auto optional_cycle = get_cycle_undirected(g);
    if (optional_cycle.has_value()) {
        const auto &cycle = *optional_cycle;
        const int sz = cycle.size();
        std::cout << sz << '\n';
        std::vector<int> vs, es;
        for (int i = 0; i < sz; ++i) {
            auto [j, eid] = cycle[i];
            vs.push_back(j);
            es.push_back(eid);
        }
        std::rotate(vs.begin(), std::prev(vs.end()), vs.end());
        for (int i = 0; i < sz; ++i) std::cout << vs[i] << " \n"[i == sz - 1];
        for (int i = 0; i < sz; ++i) std::cout << es[i] << " \n"[i == sz - 1];
    } else {
        std::cout << -1 << '\n';
    }
    return 0;
}