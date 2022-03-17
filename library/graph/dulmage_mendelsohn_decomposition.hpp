#ifndef SUISEN_DULMAGE_MENDELSOHN_DECOMPOSITION
#define SUISEN_DULMAGE_MENDELSOHN_DECOMPOSITION

#include <atcoder/scc>
#include "library/graph/bipartite_matching.hpp"

namespace suisen {
    std::vector<std::pair<std::vector<int>, std::vector<int>>> dulmage_mendelsohn_decomposition(BipartiteMatching& bm) {
        bm.solve();
        const int n = bm.left_size(), m = bm.right_size();

        std::vector<int8_t> wk_l(n, false), wk_r(m, false);
        const auto& g = bm.graph();
        auto dfs_l = [&](auto dfs_l, int i) -> void {
            if (i == BipartiteMatching::ABSENT or std::exchange(wk_l[i], true)) return;
            for (int j : g[i]) wk_r[j] = true, dfs_l(dfs_l, bm.left(j));
        };
        for (int i = 0; i < n; ++i) if (bm.right(i) == BipartiteMatching::ABSENT) dfs_l(dfs_l, i);

        std::vector<int8_t> w0_l(n, false), w0_r(m, false);
        const auto h = bm.reversed_graph();
        auto dfs_r = [&](auto dfs_r, int j) -> void {
            if (j == BipartiteMatching::ABSENT or std::exchange(w0_r[j], true)) return;
            for (int i : h[j]) w0_l[i] = true, dfs_r(dfs_r, bm.right(i));
        };
        for (int j = 0; j < m; ++j) if (bm.left(j) == BipartiteMatching::ABSENT) dfs_r(dfs_r, j);

        std::vector<std::pair<std::vector<int>, std::vector<int>>> dm;
        auto add_pair = [&](int i, int j) {
            auto& [l, r] = dm.back();
            l.push_back(i), r.push_back(j);
        };
        // W_0
        dm.emplace_back();
        for (int i = 0; i < n; ++i) if (w0_l[i]) {
            add_pair(i, bm.right(i));
        }
        for (int j = 0; j < m; ++j) if (w0_r[j] and bm.left(j) == BipartiteMatching::ABSENT) {
            dm.back().second.push_back(j);
        }
        // W_1, ..., W_{k-1}
        atcoder::scc_graph scc_g(n + m);
        for (int i = 0; i < n; ++i) {
            for (int j : g[i]) scc_g.add_edge(i, n + j);
            int j = bm.right(i); 
            if (j != BipartiteMatching::ABSENT) scc_g.add_edge(n + j, i);
        }
        for (const auto& group : scc_g.scc()) {
            if (int v0 = group.front(); (v0 < n and (w0_l[v0] or wk_l[v0])) or (v0 >= n and (w0_r[v0 - n] or wk_r[v0 - n]))) continue;
            dm.emplace_back();
            for (int i : group) if (i < n) add_pair(i, bm.right(i));
        }
        // W_k
        dm.emplace_back();
        for (int j = 0; j < m; ++j) if (wk_r[j]) {
            add_pair(bm.left(j), j);
        }
        for (int i = 0; i < n; ++i) if (wk_l[i] and bm.right(i) == BipartiteMatching::ABSENT) {
            dm.back().first.push_back(i);
        }
        return dm;
    }
} // namespace suisen


#endif // SUISEN_DULMAGE_MENDELSOHN_DECOMPOSITION
