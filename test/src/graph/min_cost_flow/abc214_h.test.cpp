#define PROBLEM "https://atcoder.jp/contests/abc214/tasks/abc214_h"

#include <iostream>

#include <atcoder/scc>

#include "library/graph/min_cost_flow.hpp"
using namespace suisen;

long long solve(int n, const std::vector<std::vector<int>> &g, const std::vector<long long> &x, int src, int k) {
    MinCostFlow<int, long long, DAG> mcf(2 * n + 1);
    const int dst = 2 * n;
    for (int u = 0; u < n; ++u) {
        for (int v : g[u]) {
            mcf.add_edge(n + u, v, k, 0);
        }
        mcf.add_edge(u, n + u, 1, -x[u]);
        mcf.add_edge(u, n + u, k - 1, 0);
        if (g[u].empty()) {
            mcf.add_edge(n + u, dst, k, 0);
        }
    }
    return -mcf.min_cost_max_flow(src, dst).second;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, k;
    std::cin >> n >> m >> k;
    atcoder::scc_graph scc_graph(n);
    std::vector<std::pair<int, int>> edges(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        edges[i] = { u, v };
        scc_graph.add_edge(u, v);
    }
    std::vector<long long> x(n);
    for (auto &e : x) std::cin >> e;
    std::vector<long long> x2;
    std::vector<int> ids(n);
    int src = 0;
    auto scc = scc_graph.scc();
    int c = scc.size();
    for (int i = 0; i < c; ++i) {
        long long sum = 0;
        for (int v : scc[i]) {
            ids[v] = i;
            sum += x[v];
            if (v == 0) src = i;
        }
        x2.push_back(sum);
    }
    std::vector<std::vector<int>> g(c);
    for (auto [u, v] : edges) {
        if (ids[u] == ids[v]) continue;
        g[ids[u]].push_back(ids[v]);
    }
    for (auto &v : g) {
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
    }
    std::cout << solve(c, g, x2, src, k) << std::endl;
    return 0;
}