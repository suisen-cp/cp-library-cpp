#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <iostream>

#include "library/graph/bipartite_matching.hpp"
using suisen::BipartiteMatching;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;
    BipartiteMatching matching(n, m);
    while (k --> 0) {
        int u, v;
        std::cin >> u >> v;
        matching.add_edge(u, v);
    }
    auto ans = matching.max_matching();
    std::cout << ans.size() << '\n';
    for (const auto &[u, v] : ans) {
        std::cout << u << ' ' << v << '\n';
    }
    return 0;
}