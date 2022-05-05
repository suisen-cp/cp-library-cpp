#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A"

#include <algorithm>
#include <iostream>

#include "library/graph/low_link.hpp"
using suisen::LowLink;

std::vector<int> solve1(int n, int m, std::vector<std::pair<int, int>> edges) {
    std::vector<int> articulation_points = LowLink(n, edges).articulation_points();
    std::sort(articulation_points.begin(), articulation_points.end());
    return articulation_points;
}

std::vector<int> solve2(int n, int m, std::vector<std::pair<int, int>> edges) {
    LowLink low_link(n);
    for (auto &[u, v] : edges) low_link.add_edge(u, v);
    low_link.build();
    std::vector<int> articulation_points = low_link.articulation_points();
    std::sort(articulation_points.begin(), articulation_points.end());
    return articulation_points;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> edges(m);
    for (auto &[u, v] : edges) std::cin >> u >> v;

    auto ans1 = solve1(n, m, edges);
    auto ans2 = solve2(n, m, edges);

    assert(ans1 == ans2);

    for (int v : ans1) {
        std::cout << v << '\n';
    }
    return 0;
}