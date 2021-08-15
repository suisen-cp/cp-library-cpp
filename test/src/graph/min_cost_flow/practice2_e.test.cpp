#define PROBLEM "https://atcoder.jp/contests/practice2/tasks/practice2_e"

#include <iostream>

#include "library/graph/min_cost_flow.hpp"
using namespace suisen;

constexpr long long INF = 1LL << 50;

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector a(n, std::vector(n, 0LL));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        std::cin >> a[i][j];
    }
    MinCostFlow<int, long long, DIJKSTRA> mcf(n + n + 2);
    int src = n + n, dst = src + 1;

    mcf.add_edge(src, dst, n * k, INF);
    for (int i = 0; i < n; ++i) {
        mcf.add_edge(src, i, k, 0);
        mcf.add_edge(i + n, dst, k, 0);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mcf.add_edge(i, j + n, 1, INF - a[i][j]);
        }
    }

    auto [flow, cost] = mcf.min_cost_max_flow(src, dst, n * k);
    long long ans = INF * flow - cost;
    std::vector g(n, std::string(n, '.'));
    for (auto e : mcf.get_edges()) {
        if (e.flow == 1 and e.from != src and e.to != dst) {
            g[e.from][e.to - n] = 'X';
        }
    }

    std::cout << ans << '\n';
    for (const auto &row : g) {
        std::cout << row << '\n';
    }
    return 0;
}