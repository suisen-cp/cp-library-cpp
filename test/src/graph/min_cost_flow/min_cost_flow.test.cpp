#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B"

#include <iostream>

#include "library/graph/min_cost_flow.hpp"
using namespace suisen;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, f;
    std::cin >> n >> m >> f;

    MinCostFlow<int, int, DIJKSTRA> mcf(n);
    for (int i = 0; i < m; ++i) {
        int u, v, cap, cost;
        std::cin >> u >> v >> cap >> cost;
        mcf.add_edge(u, v, cap, cost);
    }
    auto [flow, cost] = mcf.min_cost_max_flow(0, n - 1, f);
    if (flow == f) {
        std::cout << cost << std::endl;
    } else {
        std::cout << -1 << std::endl;
    }
    return 0;
}