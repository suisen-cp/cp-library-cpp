#ifndef SUISEN_ENUMERATE_TRIANGLES
#define SUISEN_ENUMERATE_TRIANGLES

#include <algorithm>
#include <vector>

namespace suisen {
    /**
     * Type Parameters
     * - TriangleConsumer : type of consumer function (int, int, int) -> void
     * 
     * Parameters
     * - std::vector<std::vector<int>> g : simple undirected graph
     * - TriangleConsumer fun
     * 
     * Requirements
     * - v in g[u] <=> u in g[v]
     * 
     * Complexity
     * - time : O(N + M^{3/2})
     * - space : O(N + M)
     */
    template <typename TriangleConsumer>
    void enumerate_triangles(std::vector<std::vector<int>> g, TriangleConsumer &&fun) {
        const int n = g.size();
        std::vector<int> cnt(n + 1);
        for (int i = 0; i < n; ++i) ++cnt[g[i].size() + 1];
        for (int i = 0; i < n; ++i) cnt[i + 1] += cnt[i];
        std::vector<int> ord(n), idx(n);
        for (int i = 0; i < n; ++i) ord[idx[i] = cnt[g[i].size()]++] = i;
        for (int i = 0; i < n; ++i) g[i].erase(std::remove_if(g[i].begin(), g[i].end(), [&](int j) { return idx[j] < idx[i]; }), g[i].end());
        std::vector<int8_t> exists(n, false);
        for (int i : ord) {
            for (int j : g[i]) exists[j] = true;
            for (int j : g[i]) for (int k : g[j]) if (exists[k]) fun(i, j, k);
            for (int j : g[i]) exists[j] = false;
        }
    }
} // namespace suisen

#endif // SUISEN_ENUMERATE_TRIANGLES
