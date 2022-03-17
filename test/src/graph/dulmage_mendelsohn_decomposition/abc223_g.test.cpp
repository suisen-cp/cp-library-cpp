#define PROBLEM "https://atcoder.jp/contests/abc223/tasks/abc223_g"

#include <iostream>

#include "library/graph/bipartite_graph_recognition.hpp"
#include "library/graph/dulmage_mendelsohn_decomposition.hpp"

using suisen::bipartite_coloring;
using suisen::BipartiteMatching;
using suisen::dulmage_mendelsohn_decomposition;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> col = *bipartite_coloring(g);
    std::vector<int> id(n);
    int l = 0, r = 0;
    for (int i = 0; i < n; ++i) {
        id[i] = (col[i] == 0 ? l : r)++;
    }

    BipartiteMatching bm(l, r);
    for (int i = 0; i < n; ++i) {
        if (col[i] == 1) continue;
        for (int j : g[i]) bm.add_edge(id[i], id[j]);
    }
    auto dm = dulmage_mendelsohn_decomposition(bm);

    std::cout << dm.front().second.size() + dm.back().first.size() << std::endl;

    return 0;
}