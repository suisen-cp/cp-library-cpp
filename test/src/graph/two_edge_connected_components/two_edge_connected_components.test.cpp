#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include <iostream>

#include "library/graph/two_edge_connected_components.hpp"
using suisen::TwoEdgeConnectedComponents;

auto solve1(int n, std::vector<std::pair<int, int>> edges) {
    TwoEdgeConnectedComponents tecc(n, edges);
    return std::make_pair(tecc.component_num(), tecc.groups());
}
auto solve2(int n, std::vector<std::pair<int, int>> edges) {
    TwoEdgeConnectedComponents tecc(n);
    for (auto &[u, v] : edges) {
        tecc.add_edge(u, v);
    }
    tecc.build();
    return std::make_pair(tecc.component_num(), tecc.groups());
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> edges(m);
    for (auto &[u, v] : edges) std::cin >> u >> v;

    auto ans1 = solve1(n, edges);
    auto ans2 = solve2(n, edges);

    assert(ans1 == ans2);

    const auto &[comp_num, groups] = ans1;

    std::cout << comp_num << '\n';
    for (const auto &group : groups) {
        std::cout << group.size();
        for (const int v : group) std::cout << ' ' << v;
        std::cout << '\n';
    }
    return 0;
}