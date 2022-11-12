#define PROBLEM "https://judge.yosupo.jp/problem/bipartite_edge_coloring"

#include <iostream>

#include "library/graph/edge_coloring_of_bipartite_graph.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int l, r, m;
    std::cin >> l >> r >> m;

    suisen::EdgeColoringOfBipartiteGraph g(l, r);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }
    auto [k, c] = g.solve();
    std::cout << k << '\n';
    for (auto col : c) {
        std::cout << col << '\n';
    }
    return 0;
}