#define PROBLEM "https://yukicoder.me/problems/no/1744"

#include <iostream>

#include "library/graph/dulmage_mendelsohn_decomposition.hpp"
using namespace suisen;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, l;
    std::cin >> n >> m >> l;

    std::vector<std::pair<int, int>> edges;
    BipartiteMatching bm(n, m);
    for (int i = 0; i < l; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        bm.add_edge(u, v);
        edges.emplace_back(u, v);
    }

    auto dm = dulmage_mendelsohn_decomposition(bm);
    const int k = dm.size() - 1;

    std::vector<int> cl(n), cr(m);
    for (int i = 0; i <= k; ++i) {
        for (int u : dm[i].first)  cl[u] = i;
        for (int v : dm[i].second) cr[v] = i;
    }

    for (const auto &[u, v] : edges) {
        if (cl[u] != cr[v]) {
            std::cout << "Yes\n";
        } else {
            const int i = cl[u];
            if (i == 0 or i == k) {
                std::cout << "Yes\n";
            } else if (dm[i].first.size() >= 2) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        }
    }
    return 0;
}