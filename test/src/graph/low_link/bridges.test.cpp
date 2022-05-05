#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B"

#include <algorithm>
#include <iostream>

#include "library/graph/low_link.hpp"
using suisen::LowLink;

std::vector<std::pair<int, int>> solve1(int n, int m, std::vector<std::pair<int, int>> edges) {
    std::vector<int> bridge_ids = LowLink(n, edges).bridge_ids();
    std::vector<std::pair<int, int>> bridges;
    for (auto id : bridge_ids) {
        bridges.push_back(edges[id]);
    }
    std::sort(bridges.begin(), bridges.end());
    return bridges;
}

std::vector<std::pair<int, int>> solve2(int n, int m, std::vector<std::pair<int, int>> edges) {
    LowLink low_link(n);
    for (auto &[u, v] : edges) low_link.add_edge(u, v);
    low_link.build();

    std::vector<int> bridge_ids = low_link.bridge_ids();
    std::vector<std::pair<int, int>> bridges;
    for (auto id : bridge_ids) {
        bridges.push_back(edges[id]);
    }
    std::sort(bridges.begin(), bridges.end());
    return bridges;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> edges(m);
    for (auto &[u, v] : edges) {
        std::cin >> u >> v;
        if (u > v) std::swap(u, v);
    }

    auto ans1 = solve1(n, m, edges);
    auto ans2 = solve2(n, m, edges);

    assert(ans1 == ans2);

    for (auto [u, v] : ans1) {
        std::cout << u << ' ' << v << '\n';
    }
    return 0;
}