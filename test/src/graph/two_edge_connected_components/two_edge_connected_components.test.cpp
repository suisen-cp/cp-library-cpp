#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include <iostream>

#include "library/graph/two_edge_connected_components.hpp"
using suisen::TwoEdgeConnectedComponents;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> edges(m);
    for (auto &[u, v] : edges) {
        std::cin >> u >> v;
    }
    TwoEdgeConnectedComponents tecc(n, edges);
    std::vector<std::vector<int>> c(tecc.comp_num);
    for (int v = 0; v < n; ++v) {
        c[tecc[v]].push_back(v);
    }
    std::cout << tecc.comp_num << '\n';
    for (const auto &vs : c) {
        std::cout << vs.size();
        for (const int v : vs) {
            std::cout << ' ' << v;
        }
        std::cout << '\n';
    }
    return 0;
}