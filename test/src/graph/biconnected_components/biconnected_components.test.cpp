#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"

#include <iostream>

#include "library/graph/biconnected_components.hpp"

using suisen::BiconnectedComponents;

auto solve1(int n, std::vector<std::pair<int, int>> edges) {
    BiconnectedComponents bcc(n, edges);
    return std::make_pair(bcc.component_num(), bcc.components());
}

auto solve2(int n, std::vector<std::pair<int, int>> edges) {
    BiconnectedComponents bcc(n);
    for (const auto &[u, v] : edges) bcc.add_edge(u, v);
    bcc.build();
    return std::make_pair(bcc.component_num(), bcc.components());
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> edges(m);
    for (auto &[u, v] : edges) {
        std::cin >> u >> v;
    }
    
    auto ans1 = solve1(n, edges);
    auto ans2 = solve2(n, edges);
    assert(ans1 == ans2);

    const auto &[comp_num, components] = ans1;

    std::cout << comp_num << '\n';
    for (const auto &component : components) {
        std::cout << component.vids.size();
        for (const int v : component.vids) std::cout << ' ' << v;
        std::cout << '\n';
    }

    return 0;
}