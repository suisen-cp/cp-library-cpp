#define PROBLEM "https://yukicoder.me/problems/no/1745"

#include <chrono>
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
    auto bm_start = std::chrono::system_clock::now();
    bm.solve();
    auto bm_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - bm_start).count();
    auto dm_start = std::chrono::system_clock::now();
    auto dm = dulmage_mendelsohn_decomposition(bm);
    auto dm_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - dm_start).count();

    std::cerr << "Matching  : " << bm_elapsed << " ms\n";
    std::cerr << "DM Decomp : " << dm_elapsed << " ms\n";

    const int k = dm.size() - 1;

    std::vector<int> cl(n), cr(m);
    for (int i = 0; i <= k; ++i) {
        for (int u : dm[i].first)  cl[u] = i;
        for (int v : dm[i].second) cr[v] = i;
    }

    for (const auto &[u, v] : edges) {
        if (cl[u] != cr[v]) {
            std::cout << "No\n";
        } else {
            std::cout << "Yes\n";
        }
    }
    return 0;
}