#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A"

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
    for (auto &[u, v] : edges) std::cin >> u >> v;

    std::vector<int> articulation_points = LowLink(n, edges).articulation_points;
    std::sort(articulation_points.begin(), articulation_points.end());
    for (int v : articulation_points) {
        std::cout << v << '\n';
    }
    return 0;
}