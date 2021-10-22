#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B"

#include <algorithm>
#include <iostream>

#include "library/graph/low_link.hpp"
using suisen::LowLink;

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

    std::vector<std::pair<int, int>> bridges;
    for (int edge_id : LowLink(n, edges).bridges) {
        bridges.push_back(edges[edge_id]);
    }
    std::sort(bridges.begin(), bridges.end());
    for (const auto &[u, v] : bridges) {
        std::cout << u << ' ' << v << '\n';
    }
    return 0;
}